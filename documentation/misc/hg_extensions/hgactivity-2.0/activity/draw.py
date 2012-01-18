#!/usr/bin/env python
# -*- coding: utf-8
# vim: set fileencoding=utf-8

# Copyright 2008-2011 Thomas Capricelli <orzel@freehackers.org>
# mercurial extension released under the GNU General Public Licence (GPLv2)

try:
    import matplotlib.dates as pl_dates
except:
    raise UiException('you need matplotlib in your python path in order to use the hg activity extension.')
from datetime import datetime, timedelta
from . import UiException

def convolution(datemin,datemax,data):
    date = datemin
    # convolution window
    wmin = wmax = 0
    # you can play with this number to have a more or less smooth curve
    number = 1000 # number of points we want to compute
    period = (datemax-datemin)/number # period at which we compute a value
    wperiod = period * 25 # length of the convolution window
    wperiodsec= (wperiod.days*24*3600)+wperiod.seconds
    dates, values = [], [] # return values
    mydates = data.keys()
    mydates.sort()
    length=len(mydates)
    for x in xrange(number):
        date += period
        while wmin<length and mydates[wmin]<date-wperiod:
            wmin+=1
        while wmax<length and mydates[wmax]<date+wperiod:
            wmax+=1
        value = 0.
        for a in range(wmin,wmax):
            delta = mydates[a]-date
            deltasec= abs((delta.days*24*3600)+delta.seconds)
            value += data[mydates[a]]* (1-float(deltasec)/float(wperiodsec))
        values.append(value)
        dates.append(date)
    return dates, values
   
def draw_graph(fig, options, dates_tab):
    years    = pl_dates.YearLocator()   # every year
    months   = pl_dates.MonthLocator()  # every month
    days = pl_dates.DayLocator()  # every month
    yearsFmt = pl_dates.DateFormatter('%Y')
    monthsFmt = pl_dates.DateFormatter('%b \'%y')
    daysFmt = pl_dates.DateFormatter('%d %b')
    mondays  = pl_dates.WeekdayLocator(pl_dates.MONDAY)

    # default datemin/max (if not set by user) is the min/maximum date
    # available in sets.
    datemin = options.datemin
    if datemin is None:
        datemin = min([min(d.keys()) for d in  dates_tab.values()])
    datemax = options.datemax
    if datemax is None:
        datemax = max([max(d.keys()) for d in  dates_tab.values()])

    if datemax<datemin:
        raise UiException( "Invalid values for datemin (%s) and datemax (%s)" % (datemin, datemax) )
    period = datemax-datemin
    # prevent ugly display if the period is really too short
    if period.days<3:
        datemin -= timedelta(2)
        datemax += timedelta(2)
    if options.datemin is None:
        try:
            datemin -= period/20 # 5%
        except OverflowError, e:
            raise UiException(str(e))
    # if we are more than 15% ahead the last commit, we should use now() as
    # last date
    # (unless, of course, the user provided a datemax, ...)
    if options.datemax is None and datetime.now()>datemax + 3*period/20:
        datemax = datetime.now()

    # compare contributions
    contribs = dates_tab.keys()
    contribs.sort(key= lambda k : -len(dates_tab[k]))
    contribs=contribs[0:min(len(contribs),max(5,options.maxcaptions))] # only keeps the best ones for display

    # create plot
    fig.clear()
    ax = fig.add_subplot(111)

    # see both http://en.wikipedia.org/wiki/Web_colors and
    # http://matplotlib.sourceforge.net/api/colors_api.html
    ax.set_color_cycle(['blue', 'lime', 'red', 'aqua', 'fuchsia', 'yellow', 'black', 'green', 'maroon', 'navy', 'olive', 'purple', 'grey', 'silver', 'teal' ])

    for title in contribs:
        dates, values = convolution(datemin, datemax, dates_tab[title])
        ax.plot( dates, values, label=options.titlemap.get(title, title), linewidth=1.5)

    # display tags
    if options.showtags:
        tagypos = 0
        for date, name in options.tags:
            ax.plot_date([date], [00], 'ro')
    #        ax.plot([date.toordinal()], [0], 'bo')
            t=date.time()
            x= float((t.hour*60)+t.minute)*60/float(24*60*60) + float(date.toordinal())
            ax.text(x, 0, name,
            withdash=True, dashdirection=0, dashlength=50+tagypos, rotation='horizontal', dashrotation='vertical')
            tagypos += 20
            if tagypos>90:
                tagypos=0
    else:
        pass

    # format the ticks
    if (datemax-datemin).days>600:
        ax.xaxis.set_major_locator(years)
        ax.xaxis.set_major_formatter(yearsFmt)
        ax.xaxis.set_minor_locator(months)
    elif (datemax-datemin).days>30:
        ax.xaxis.set_major_locator(months)
        ax.xaxis.set_major_formatter(monthsFmt)
        ax.xaxis.set_minor_locator(mondays)
    else:
        ax.xaxis.set_major_locator(days)
        ax.xaxis.set_major_formatter(daysFmt)

    ax.set_xlim(datemin,datemax)
    ax.yaxis.set_visible(False)

    # format the coords message box
    ax.format_xdata = pl_dates.DateFormatter('%Y-%m-%d')
    ax.format_ydata = None
    ax.grid(True)

    # rotates and right aligns the x labels, and moves the bottom of the
    # axes up to make room for them
    fig.autofmt_xdate()
    fig.suptitle(options.imagetitle,fontsize=12)
    # setup legend
    if len(dates_tab)<=options.maxcaptions:
        ax.legend(loc='best', shadow=True)
    else:
        ax.legend(contribs[0:options.maxcaptions], loc='best', shadow=True)
    
# vim: ai ts=4 sts=4 et sw=4
