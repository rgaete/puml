#!/usr/bin/env python
# -*- coding: utf-8
# vim: set fileencoding=utf-8

# Copyright 2010 Frédéric MOULIN <moulinfr@gmail.com>
# Copyright 2011 Thomas Capricelli <orzel@freehackers.org>

"""
Test script for activity module.
"""
import datetime
import os
import unittest
import tempfile
import time

import mercurial.commands
import mercurial.hg
import mercurial.ui

import activity

class Mockhg:

    def create(self, ui, reponame):
        return mercurial.hg.repository(ui, reponame, create = 1)

    def add(self, ui, repo, filename):
        mercurial.commands.add(ui, repo, filename)

    def commit(self, ui, repo, filename, message = '', user = '', date = ''):
        if not message:
            message = 'Added %s.' % filename
        if not user:
            user = 'jdoe'
        if not date:
            date = str(int(time.time())) + ' 0'
        mercurial.commands.commit(ui, repo, filename, message = message, user = user, date = date)

class Mockui(mercurial.ui.ui):

    __write = []
    __status = []
    __warn = []

    def write(self, msg):
        self.__write.append(msg)
        print '[write]', msg

    def pop_write(self):
        return self.__write.pop(0)
             
    def warn(self, msg):
        self.__warn.append(msg)
        print '[warn]', msg
        
    def pop_warn(self):
        return self.__warn.pop(0)
     
    def status(self, msg):
        self.__status.append(msg)
        print '[status]', msg
        
    def pop_status(self):
        return self.__status.pop(0)

    def clear(self):
        Mockui.__write = []
        Mockui.__status = []
        Mockui.__warn = []

def deltree(fname):
    if not os.path.exists(fname):
        return
    for f in os.listdir(fname):
        fullname = os.path.join(fname, f)
        if os.path.isdir(fullname):
            deltree(fullname)
        else:
            try:
                os.unlink(fullname)
            except:
                pass
    try:
        os.rmdir(fname)
    except:
        pass
        
class TestActivity(unittest.TestCase):
    '''
    Unit tests for the nostat function.
    '''

    def setUp(self):
        # we create a test repository
        self.ui = Mockui()
        self.hg = Mockhg()
        self.reponame = tempfile.mkdtemp(prefix = 'hgactivity.')
        # clean-up
        deltree(self.reponame)
        self.repo = self.hg.create(self.ui, self.reponame)

        self.defaultoptions = {
            'maxcaptions': 4,
            'datemax': '',
            'datemin': '',
            'imagetitle': '',
            'aliases': '',
            'hidetags': False,
            'height': 600,
            'width': 800,
            'uselines': False,
            'skipmerges': False,
            'split': 'none',
            'exclude': '',
            'filename': 'activity.png',
            'mode': 'file'
        }

    def xtestnostat(self):
        output = activity.nostat(None, None)
        self.assertEqual(output, (1, 0))

    def testempty(self):
        # check that the user is warned when there are no data
        self.assertRaises(SystemExit, activity.activity, self.ui, self.repo, **self.defaultoptions)
        self.assertEqual(self.ui.pop_write(), 'There are 0 changesets\n')
        self.assertEqual(self.ui.pop_warn(), 'Hg activity, checking options: no data available with those options.\n')
    
    def testsimple(self):
        # create a dummy file
        filename = os.path.join(self.reponame, 'foo')
        f = file(filename, 'w')
        f.close()
        
        # add the dummy file to the repository and commit
        self.hg.add(self.ui, self.repo, filename)
        self.hg.commit(self.ui, self.repo, filename)
        
        # clear hg logs
        self.ui.clear()

        # check that a simple activity diagram can be generated
        activity.activity(self.ui, self.repo, **self.defaultoptions)
        self.assertRaises(IndexError, self.ui.pop_warn)
        self.assertEqual(self.ui.pop_write(), 'There are 1 changesets\n')
        self.assertEqual(self.ui.pop_status(), 'Created the file \'activity.png\'\n')

    def testdatemin(self):
        # create a dummy file
        filename = os.path.join(self.reponame, 'foo')
        f = file(filename, 'w')
        f.close()
        
        # add the dummy file to the repository and commit
        self.hg.add(self.ui, self.repo, filename)
        self.hg.commit(self.ui, self.repo, filename, date = '0 0') # date is a "unixtime offset" string
        
        # check that the period is too big
        options = self.defaultoptions.copy()
        options['datemin']='0001-01-01'
        self.assertRaises(SystemExit, activity.activity, self.ui, self.repo, **options)
        self.assertEqual(self.ui.pop_warn(), 'Hg activity, checking options: invalid --datemin value. The minimal accepted value is 1900-01-01\n');

        # check that no data were found for datemin set after the commit
        options['datemin']='2001-01-01'
        self.assertRaises(SystemExit, activity.activity, self.ui, self.repo, **options)
        self.assertEqual(self.ui.pop_write(), 'There are 1 changesets\n')
        self.assertEqual(self.ui.pop_warn(), 'Hg activity, checking options: no data available with those options.\n')

    def testdatemax(self):
        # create a dummy file
        filename = os.path.join(self.reponame, 'foo')
        f = file(filename, 'w')
        f.close()
        
        # add the dummy file to the repository and commit
        self.hg.add(self.ui, self.repo, filename)
        self.hg.commit(self.ui, self.repo, filename, date = '0 0')
        
        # check that no data were found for datemax set before the commit
        options = self.defaultoptions.copy()
        options['datemax']='1900-01-01'
        self.assertRaises(SystemExit, activity.activity, self.ui, self.repo, **options)
        self.assertEqual(self.ui.pop_write(), 'There are 1 changesets\n')
        self.assertEqual(self.ui.pop_warn(), 'Hg activity, checking options: no data available with those options.\n')

        # check that data are found for datemax set after the commit
        options['datemax']='2000-01-01'
        activity.activity(self.ui, self.repo, **options)
        self.assertEqual(self.ui.pop_write(), 'There are 1 changesets\n')
        self.assertEqual(self.ui.pop_status(), 'Created the file \'activity.png\'\n')

    def testperiod(self):
        # create a dummy file
        filename = os.path.join(self.reponame, 'foo')
        f = file(filename, 'w')
        f.close()

        # add the dummy file to the repository and commit
        self.hg.add(self.ui, self.repo, filename)
        self.hg.commit(self.ui, self.repo, filename)
        
        # back in time 40 days ago
        dday = datetime.datetime.today() - datetime.timedelta(40)

        # check that an activity diagram can be generated for a period greater than 30 days
        options = self.defaultoptions.copy()
        options['datemin']=dday.strftime('%Y-%m-%d')
        activity.activity(self.ui, self.repo, **options)
        self.assertEqual(self.ui.pop_write(), 'There are 1 changesets\n')
        self.assertEqual(self.ui.pop_status(), 'Created the file \'activity.png\'\n')
        
    def testsplitauthors(self):
        # create a dummy file
        filename = os.path.join(self.reponame, 'foo')
        f = file(filename, 'w')
        f.close()
        
        # add the dummy file to the repository and commit
        self.hg.add(self.ui, self.repo, filename)
        self.hg.commit(self.ui, self.repo, filename)

        # create another dummy file
        filename = os.path.join(self.reponame, 'bar')
        f = file(filename, 'w')
        f.close()
        
        # add the dummy file to the repository and commit
        self.hg.add(self.ui, self.repo, filename)
        self.hg.commit(self.ui, self.repo, filename, user = 'tux')

        # check that an author-based activity diagram can be generated
        options = self.defaultoptions.copy()
        options['split']='authors'
        activity.activity(self.ui, self.repo, **options)
        self.assertEqual(self.ui.pop_write(), 'There are 2 changesets\n')
        self.assertEqual(self.ui.pop_status(), 'Created the file \'activity.png\'\n')

    def testsplitfiles(self):
        # create a dummy file
        filename = os.path.join(self.reponame, 'foo')
        f = file(filename, 'w')
        f.close()
        
        # add the dummy file to the repository and commit
        self.hg.add(self.ui, self.repo, filename)
        self.hg.commit(self.ui, self.repo, filename)

        # create another dummy file
        filename = os.path.join(self.reponame, 'bar')
        f = file(filename, 'w')
        f.close()
        
        # add the dummy file to the repository and commit
        self.hg.add(self.ui, self.repo, filename)
        self.hg.commit(self.ui, self.repo, filename)

        # create another dummy file again
        filename = os.path.join(self.reponame, 'baz')
        f = file(filename, 'w')
        f.close()
        
        # add the dummy file to the repository and commit
        self.hg.add(self.ui, self.repo, filename)
        self.hg.commit(self.ui, self.repo, filename)

        # patch the last file and commit changes 
        filename = os.path.join(self.reponame, 'baz')
        f = file(filename, 'w')
        f.write('Hello world!')
        f.close()        
        self.hg.commit(self.ui, self.repo, filename)
        
        # check that a file-based activity diagram can be generated
        options = self.defaultoptions.copy()
        options['split']='files'
        activity.activity(self.ui, self.repo, **options)
        self.assertEqual(self.ui.pop_write(), 'There are 4 changesets\n')
        self.assertEqual(self.ui.pop_status(), 'Created the file \'activity.png\'\n')

    def tearDown(self):
        # clean-up
        self.ui.clear()
        deltree(self.reponame)
        
        # wait for repo deletion to be completed
        while (os.path.exists(self.reponame)):
            time.sleep(1)

def cover(suite):
    # start code coverage
    ignore_pylibs = True
    figleaf.start(ignore_pylibs)
    
    try:
        # run test suite
        results = unittest.TextTestRunner(verbosity = 2).run(suite)
    except Exception, e:
        print '!!', e
    
    # stop code coverage
    figleaf.stop()
    
    # write code coverage results
    cwd = os.getcwd()
    figleaf.write_coverage(os.path.join(cwd, '.figleaf'))
    
    # read code coverage results
    try:
        coverage = figleaf.read_coverage('.figleaf')
    except IOError:
        print 'Failed to read coverage file'
        sys.exit(1)

    # build a html report with annotated source
    exclude = []
    files = { os.path.join(cwd, 'activity.py'):  1 }
    figleaf.annotate_html.prepare_reportdir(cwd)
    figleaf.annotate_html.report_as_html(coverage, cwd, exclude, files)
    print 'figleaf: HTML output written to %s' % (cwd,)
    
    # display html report
    try:
        # @NOTE: the method startfile is only available on Windows platforms
        os.startfile('_MM_Hgactivity_activity.py.html')
    except AttributeError:
        pass

if __name__ == '__main__':
    # build a test suite from test cases
    suite = unittest.TestLoader().loadTestsFromTestCase(TestActivity)
        
    # check if figleaf module is available (for test code coverage)
    try:
        import figleaf
        import figleaf.annotate_html
    except ImportError:
        # run test suite
        results = unittest.TextTestRunner(verbosity = 2).run(suite)
    else:
        # run test suite with code coverage
        results = cover(suite)

# vim: ai ts=4 sts=4 et sw=4
