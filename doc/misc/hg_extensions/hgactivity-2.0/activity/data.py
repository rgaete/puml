#!/usr/bin/env python
# -*- coding: utf-8
# vim: set fileencoding=utf-8

# Copyright 2008-2011 Thomas Capricelli <orzel@freehackers.org>
# mercurial extension released under the GNU General Public Licence (GPLv2)

from os import path
from datetime import datetime
from mercurial import patch, util
from mercurial.templatefilters import person

def nostat(ctx, options):
    return 1, 0

def diffstat(ctx, options):
    parents = ctx.parents()
    if len(parents)!=1: return (0,0)  # merge
    adds = 0
    removes = 0
    diff = ''.join(patch.diff(options.repo, parents[0].node(), ctx.node()))
    for l in diff.split('\n'):
        if l.startswith('+') and not l.startswith('+++ '):
            adds += 1
        elif l.startswith('-') and not l.startswith('--- '):
            removes += 1
    return adds, removes

def collect_data(cl,options):
    if options.split=='none':
        fetch_data = fetch_data_any
    else:
        fetch_data = globals()['fetch_data_' + options.split]
    stat_maker = nostat
    if options.uselines:
        stat_maker = diffstat
    # starting with mercurial 1.1, this could be simplified by iterating in cl directly    
    data = {}
    for i in xrange(options.length):
        node = cl.read(cl.node(i))
        # Check whether the number of changed files == 0
        if options.skipmerges and len(node[3]) == 0:
        	continue # Skip merges
        # find out date and filter
        date = datetime.fromtimestamp(node[2][0])
        if options.datemin!=None and date<options.datemin:
            continue
        if options.datemax!=None and date>options.datemax:
            continue
        # find out who this is
        who = node[1]
        email = util.email(who)
        if email in options.exclude:
            continue
        ctx = options.repo.changectx(i)
        for k, v in fetch_data(ctx, stat_maker, options):            
            if not data.has_key(k):
                data[k] = {}
            data[k][date] = sum(v)

    # post_collect_data
    titlemap = {}
    if options.split=='authors':
        for who in data.keys():
            email = util.email(who)
            titlemap[email] = person(who)
    options.titlemap = titlemap
    return data

def fetch_data_any(ctx, stat_maker, options):
    # data only contains one entry for the global graphic
    yield 'Overall activity', stat_maker(ctx, options)
    
def fetch_data_authors(ctx, stat_maker, options):
    localstat = stat_maker(ctx, options)
    # data is dictionnary mapping an author name to the data for
    # this author
    email = util.email(ctx.user())
    email = options.amap.get(email, email) # alias remap
    yield email, localstat

def fetch_data_files(ctx, stat_maker, options):
    localstat = stat_maker(ctx, options)
    for filename in ctx.files():
        yield filename, localstat

def fetch_data_branches(ctx, stat_maker, options):
    yield ctx.branch() , stat_maker(ctx, options)

def fetch_data_directories(ctx, stat_maker, options):
    localstat = stat_maker(ctx, options)
    dirs = [ path.split(filename)[0] for filename in ctx.files()]
    dirs = list(set(dirs)) # remove duplicate
    if '' in dirs:
        dirs[dirs.index('')] = '<main directory>'
    for dir in dirs:
        yield dir , localstat

# vim: ai ts=4 sts=4 et sw=4
