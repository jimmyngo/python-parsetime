/* 
 *  parsetime.c - parse time for at(1)
 *  Copyright (C) 1993, 1994  Thomas Koenig
 *
 *  modifications for English-language times
 *  Copyright (C) 1993  David Parsons
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. The name of the author(s) may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  at [NOW] PLUS NUMBER MINUTES|HOURS|DAYS|WEEKS
 *     /NUMBER [DOT NUMBER] [AM|PM] [UTC]\ /[MONTH NUMBER [NUMBER]]             \
 *     |NOON                             | |[TOMORROW]                          |
 *     |MIDNIGHT                         | |[DAY OF WEEK]                       |
 *     \TEATIME                          / |NUMBER [SLASH NUMBER [SLASH NUMBER]]|
 *                                         \PLUS NUMBER MINUTES|HOURS|DAYS|WEEKS/
 */

/* System Headers */

#include <sys/types.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

/* Local headers */
#include "parsetime.h"


/* Structures and unions */

/* errors */
enum {
    GARBLED_TIME, INCOMPLETE_TIME
};

const char *ErrorMessages[2] = {
    "garbled time",
    "incomplete_time",
};

/* symbols */
enum {
    MIDNIGHT, NOON, TEATIME,
    PM, AM, UTC, TOMORROW, TODAY, NOW,
    SECONDS, MINUTES, HOURS, DAYS, WEEKS, MONTHS, YEARS,
    NUMBER, PLUS, MINUS, DOT, SLASH, ID, JUNK,
    JAN, FEB, MAR, APR, MAY, JUN,
    JUL, AUG, SEP, OCT, NOV, DEC,
    SUN, MON, TUE, WED, THU, FRI, SAT
};

/* parse translation table - table driven parsers can be your FRIEND!  */
static const struct {
    const char *name;   /* token name */
    int value;          /* token id */
} Specials[] = {
    { "midnight", MIDNIGHT }, /* 00:00:00 of today or tomorrow */
    { "noon", NOON },         /* 12:00:00 of today or tomorrow */
    { "teatime", TEATIME },   /* 16:00:00 of today or tomorrow */
    { "am", AM },             /* morning times for 0-12 clock */
    { "pm", PM },             /* evening times for 0-12 clock */
    { "utc", UTC},            /* UTC timezone */
    { "tomorrow", TOMORROW }, /* execute 24 hours from time */
    { "today", TODAY },       /* execute today - don't advance time */
    { "now", NOW },           /* opt prefix for PLUS/MINUS */
    { "n", NOW },             /* opt prefix for PLUS/MINUS */

    { "second", SECONDS },    /* seconds multiplier */
    { "seconds", SECONDS },   /* (pluralized) */
    { "sec", SECONDS },       /* (shortened) */
    { "s", SECONDS },         /* (shortened) */
    { "minute", MINUTES },    /* minutes ... */
    { "minutes", MINUTES },   /* (pluralized) */
    { "min", MINUTES },       /* (shortened) */
    { "hour", HOURS },        /* hours ... */
    { "hours", HOURS },       /* (pluralized) */
    { "hr", HOURS },          /* (shortened) */
    { "h", HOURS },           /* (shortened) */
    { "day", DAYS },          /* days ... */
    { "days", DAYS },         /* (pluralized) */
    { "d", DAYS },            /* (shortened) */
    { "week", WEEKS },        /* week ... */
    { "weeks", WEEKS },       /* (pluralized) */
    { "wk", WEEKS },          /* (shortened) */
    { "w", WEEKS },           /* (shortened) */
    { "month", MONTHS },      /* month ... */
    { "months", MONTHS },     /* (pluralized) */
    { "mon", MONTHS },        /* (shortened) */
    { "year", YEARS },        /* year ... */
    { "years", YEARS },       /* (pluralized) */
    { "yr", YEARS },          /* (shortened) */
    { "y", YEARS },           /* (shortened) */

    { "jan", JAN },
    { "feb", FEB },
    { "mar", MAR },
    { "apr", APR },
    { "may", MAY },
    { "jun", JUN },
    { "jul", JUL },
    { "aug", AUG },
    { "sep", SEP },
    { "oct", OCT },
    { "nov", NOV },
    { "dec", DEC },
    { "january", JAN },
    { "february", FEB },
    { "march", MAR },
    { "april", APR },
    { "may", MAY },
    { "june", JUN },
    { "july", JUL },
    { "august", AUG },
    { "september", SEP },
    { "october", OCT },
    { "november", NOV },
    { "december", DEC },
    { "sunday", SUN },
    { "sun", SUN },
    { "monday", MON },
    { "mon", MON },
    { "tuesday", TUE },
    { "tue", TUE },
    { "wednesday", WED },
    { "wed", WED },
    { "thursday", THU },
    { "thu", THU },
    { "friday", FRI },
    { "fri", FRI },
    { "saturday", SAT },
    { "sat", SAT },
} ;

/* File scope variables */

static char **scp;  /* scanner - pointer at arglist */
static char scc;    /* scanner - count of remaining arguments */
static char *sct;   /* scanner - next char pointer in current argument */
static int need;    /* scanner - need to advance to next argument */

static char *sc_token;  /* scanner - token buffer */
static size_t sc_len;   /* scanner - length of token buffer */
static int sc_tokid;    /* scanner - token id */

static int seconds_defined; /* If seconds has been set */
static int utc_defined; /* If utc has been set */
static int ret_code; /* If utc has been set */


/* Local functions */

void usage () {
    fprintf(stderr, "usage: parsetime [timespec]\n");
    exit(1);
}

void panic (int error) {
    fprintf(stderr, "%s\n", ErrorMessages[error]);
    ret_code = 1;
}

/*
 * parse a token, checking if it's something special to us
 */
static int
parse_token(char *arg)
{
    size_t i;

    for (i = 0; i < (sizeof Specials / sizeof Specials[0]); i++)
    if (strcasecmp(Specials[i].name, arg) == 0) {
        return sc_tokid = Specials[i].value;
    }

    /* not special - must be some random id */
    return ID;
} /* parse_token */


/*
 * init_scanner() sets up the scanner to eat arguments
 */
static void
init_scanner(int argc, char **argv)
{
    scp = argv;
    scc = argc;
    need = 1;
    sc_len = 1;
    while (argc-- > 0) {
        sc_len += strlen(*argv++);
    }

    if ((sc_token = malloc(sc_len)) == NULL) {
        errx(EXIT_FAILURE, "virtual memory exhausted");
    }
} /* init_scanner */

/*
 * token() fetches a token from the input stream
 */
static int
token(void)
{
    int idx;

    while (1) {
        memset(sc_token, 0, sc_len);
        sc_tokid = EOF;
        idx = 0;

        /* if we need to read another argument, walk along the argument list;
         * when we fall off the arglist, we'll just return EOF forever
         */
        if (need) {
            if (scc < 1)
            return sc_tokid;
            sct = *scp;
            scp++;
            scc--;
            need = 0;
        }
        /* eat whitespace now - if we walk off the end of the argument,
         * we'll continue, which puts us up at the top of the while loop
         * to fetch the next argument in
         */
        while (isspace(*sct)) {
            ++sct;
        }
        if (!*sct) {
            need = 1;
            continue;
        }

        /* preserve the first character of the new token
         */
        sc_token[0] = *sct++;

        /* then see what it is
         */
        if (isdigit(sc_token[0])) {
            while (isdigit(*sct)) {
                sc_token[++idx] = *sct++;
            }
            sc_token[++idx] = 0;
            return sc_tokid = NUMBER;
        }
        else if (isalpha(sc_token[0])) {
            while (isalpha(*sct)) {
                sc_token[++idx] = *sct++;
            }
            sc_token[++idx] = 0;
            return parse_token(sc_token);
        }
        else if (sc_token[0] == ':' || sc_token[0] == '.') {
            return sc_tokid = DOT;
        }
        else if (sc_token[0] == '+') {
            return sc_tokid = PLUS;
        }
        else if (sc_token[0] == '-') {
            return sc_tokid = MINUS;
        }
        else if (sc_token[0] == '/') {
            return sc_tokid = SLASH;
        }
        else {
            return sc_tokid = JUNK;
        }
    } /* while (1) */
} /* token */


/*
 * plonk() gives an appropriate error message if a token is incorrect
 */
static void
plonk(int tok)
{
    panic((tok == EOF) ? INCOMPLETE_TIME : GARBLED_TIME);
} /* plonk */


/*
 * expect() gets a token and dies most horribly if it's not the token we want
 */
static void
expect(const int desired)
{
    if (token() != desired) {
        /* and we die here... */
        plonk(sc_tokid);
    }
} /* expect */


/*
 * plus_or_minus() holds functionality common to plus() and minus()
 */
static void
plus_or_minus(struct tm *tm, float delay)
{
    switch (token()) {
        case YEARS:
            {
                int years = delay;
                tm->tm_year += years;
                /* Decimal years are estimated based on 365 days */
                delay = (delay - years) * 31536000;
                break;
            }
        case MONTHS:
            {
                int months = delay;
                tm->tm_mon += months;
                /* Decimal months are estimated based on 30 days */
                delay = (delay - months) * 2592000;
                break;
            }
        case WEEKS:
            delay *= 604800;
            break;
        case DAYS:
            delay *= 86400;
            break;
        case HOURS:
            delay *= 3600;
            break;
        case MINUTES:
            delay *= 60;
            break;
        case SECONDS:
            break;
        default:
            plonk(sc_tokid);
            break;
    }

    tm->tm_sec += delay;

    tm->tm_isdst = -1;
    if (mktime(tm) < 0) {
        plonk(sc_tokid);
    }
} /* plus_or_minus */


/*
 * plus_minus() parses a now + time
 *
 *  at [NOW] [PLUS|MINUS] NUMBER [SECONDS|MINUTES|HOURS|DAYS|WEEKS|MONTHS|YEARS]
 *
 */
static void
plusminus(struct tm *tm)
{
    int op_token;
    int float_len, token_len;
    char* float_value;
    float delay;

    float_len = 0;
    while (sc_tokid != EOF) {
        switch(sc_tokid) {
            case MINUS:
            case PLUS:
                op_token = sc_tokid;
                expect(NUMBER);

                /* Look for decimal value for increments */
                if (*sct == '.') {
                    /* float_value will have concatinated floating point reconstructed */
                    if ((float_value = malloc((strlen(sc_token) + 1) * sizeof(char))) == NULL) {
                        errx(EXIT_FAILURE, "virtual memory exhausted");
                    }

                    /* Copy numbers before the decimal */
                    token_len = strlen(sc_token);
                    memcpy(float_value, sc_token,token_len);
                    float_len += token_len;

                    /* Skip decimal */
                    sct++;
                    expect(NUMBER);

                    /* Reinsert the decimal */
                    float_value[float_len] = '.';
                    float_value[float_len + 1] = '\0';

                    /* Copy numbers after the decimal */
                    float_len += strlen(sc_token);
                    if ((float_value = realloc(float_value, float_len * sizeof(char))) == NULL) {
                        errx(EXIT_FAILURE, "virtual memory exhausted");
                    }

                    strncat(float_value, sc_token, strlen(sc_token));
                } else {
                    float_value = sc_token;
                }

                delay = atof(float_value); if (op_token == MINUS) {
                    delay = -delay;
                }

                plus_or_minus(tm, delay);
                if (float_len > 0) {
                    free(float_value);
                }
                break;
        }
        token();
    }
}


/*
 * tod() computes the time of day
 *     [NUMBER [DOT NUMBER] [AM|PM]] [UTC]
 */
static void
tod(struct tm *tm)
{
    int hour;
    int minute = 0;
    int second = 0;
    int tlen;

    hour = atoi(sc_token);
    tlen = strlen(sc_token);

    /* first pick out the time of day - if it's 4 digits, we assume
     * a HHMM time, otherwise it's HH DOT MM time or HH DOT MM DOT SS
     */
    if (token() == DOT) {
        expect(NUMBER);
        minute = atoi(sc_token);
        if (minute > 59) {
            panic(GARBLED_TIME);
        }
        if (token() == DOT) {
            expect(NUMBER);
            seconds_defined = 1;
            second = atoi(sc_token);
            if (second > 59) {
                panic(GARBLED_TIME);
            }
            token();
        };
    }
    else if (tlen == 4) {
        minute = hour % 100;
        if (minute > 59) {
            panic(GARBLED_TIME);
        }
        hour = hour / 100;
    }
    else if (tlen == 6) {
        seconds_defined = 1;
        second = (hour % 100);
        if (second > 59) {
            panic(GARBLED_TIME);
        }
        minute = (hour % 10000) / 100;
        if (minute > 59) {
            panic(GARBLED_TIME);
        }
        hour = hour / 10000;
    }

    /* check if an AM or PM specifier was given
     */
    if (sc_tokid == AM || sc_tokid == PM) {
        if (hour > 12) {
            panic(GARBLED_TIME);
        }

        if (sc_tokid == PM) {
            /* 12:xx PM is 12:xx, not 24:xx */
            if (hour != 12) {
                hour += 12;
            }
        } else {
            /* 12:xx AM is 00:xx, not 12:xx */
            if (hour == 12) {
                hour = 0;
            }
        }
        token();
    } else if (hour > 23) {
        panic(GARBLED_TIME);
    }

    if (sc_tokid == UTC) {
        /* Handle UTC offset */
        hour += tm->tm_gmtoff / 3600;
        hour %= 24;
        minute += tm->tm_gmtoff / 60;
        minute %= 60;
        tm->tm_gmtoff = 0;
        utc_defined = 1;
        token();
    }

    /* if we specify an absolute time, we don't want to bump the day even
     * if we've gone past that time - but if we're specifying a time plus
     * a relative offset, it's okay to bump things
     */
    if ((sc_tokid == EOF || sc_tokid == PLUS || sc_tokid == MINUS) && tm->tm_hour > hour) {
        tm->tm_mday++;
        tm->tm_wday++;
    }

    tm->tm_hour = hour;
    tm->tm_min = minute;
    tm->tm_sec = second;
    if (tm->tm_hour == 24) {
        tm->tm_hour = 0;
        tm->tm_mday++;
    }
} /* tod */


/*
 * assign_date() assigns a date, wrapping to next year if needed
 */
static void
assign_date(struct tm *tm, long mday, long mon, long year)
{

   /*
    * Convert year into tm_year format (year - 1900).
    * We may be given the year in 2 digit, 4 digit, or tm_year format.
    */
    if (year != -1) {
        if (year >= 1900) {
            /* convert from 4 digit year */
            year -= 1900;
        } else if (year < 100) {
            /* convert from 2 digit year */
            struct tm *lt;
            time_t now;

            time(&now);
            lt = localtime(&now);

            /* Convert to tm_year assuming current century */
            year += (lt->tm_year / 100) * 100;

            if (year == lt->tm_year - 1) {
                year++;
            } else if (year < lt->tm_year) {
                /* must be in next century */
                year += 100;
            }
        }
    }

    if (year < 0 && (tm->tm_mon > mon ||(tm->tm_mon == mon && tm->tm_mday > mday))) {
        year = tm->tm_year + 1;
    }

    tm->tm_mday = mday;
    tm->tm_mon = mon;

    if (year >= 0) {
        tm->tm_year = year;
    }
} /* assign_date */


/* 
 * month() picks apart a month specification
 *
 *  /[<month> NUMBER [NUMBER]]           \
 *  |[TOMORROW]                          |
 *  |[DAY OF WEEK]                       |
 *  |NUMBER [SLASH NUMBER [SLASH NUMBER]]|
 *  \PLUS NUMBER MINUTES|HOURS|DAYS|WEEKS/
 */
static void
month(struct tm *tm)
{
    long year= (-1);
    long mday = 0, wday, mon;
    int tlen;

    /* Reset seconds if we're not dealing with NOW */
    if (seconds_defined == 0) {
        tm->tm_sec = 0;
    }
    switch (sc_tokid) {
        case TOMORROW:
            /* do something tomorrow */
            tm->tm_mday ++;
            tm->tm_wday ++;
        case TODAY:	/* force ourselves to stay in today - no further processing */
            token();
            break;

        case JAN: case FEB: case MAR: case APR: case MAY: case JUN:
        case JUL: case AUG: case SEP: case OCT: case NOV: case DEC:
            /* do month mday [year]
            */
            mon = (sc_tokid-JAN);
            expect(NUMBER);
            mday = atol(sc_token);
            if (token() == NUMBER) {
                year = atol(sc_token);
                token();
            }
            assign_date(tm, mday, mon, year);
            break;

        case SUN: case MON: case TUE:
        case WED: case THU: case FRI:
        case SAT:
            /* do a particular day of the week
            */
            wday = (sc_tokid-SUN);

            mday = tm->tm_mday;

            /* if this day is < today, then roll to next week
            */
            if (wday < tm->tm_wday) {
                mday += 7 - (tm->tm_wday - wday);
            } else {
                mday += (wday - tm->tm_wday);
            }

            tm->tm_wday = wday;

            assign_date(tm, mday, tm->tm_mon, tm->tm_year);
            break;

        case NUMBER:
            /* get numeric MMDDYY, mm/dd/yy, or dd.mm.yy
            */
            tlen = strlen(sc_token);
            mon = atol(sc_token);
            token();

            if (sc_tokid == SLASH || sc_tokid == DOT) {
                int sep;

                sep = sc_tokid;
                expect(NUMBER);
                mday = atol(sc_token);
                if (token() == sep) {
                    expect(NUMBER);
                    year = atol(sc_token);
                    token();
                }

                /* flip months and days for European timing
                */
                if (sep == DOT) {
                    int x = mday;
                    mday = mon;
                    mon = x;
                }
            } else if (tlen == 6 || tlen == 8) {
                if (tlen == 8) {
                    year = (mon % 10000) - 1900;
                    mon /= 10000;
                } else {
                    year = mon % 100;
                    mon /= 100;
                }
                mday = mon % 100;
                mon /= 100;
            } else {
                panic(GARBLED_TIME);
            }

            mon--;
            if (mon < 0 || mon > 11 || mday < 1 || mday > 31) {
                panic(GARBLED_TIME);
            }

            assign_date(tm, mday, mon, year);
            break;
    } /* case */
    switch (sc_tokid) {
        case PLUS:
        case MINUS:
            plusminus(tm);
            break;

    } /* case */
} /* month */


/* Global functions */

int
parsetime(int token_nr, char **token_arr, time_t *result)
{
/* Do the argument parsing, die if necessary, and return the time the job
 * should be run.
 */
    time_t nowtimer, runtimer;
    struct tm nowtime, runtime;
    int hr = 0;
    /* this MUST be initialized to zero for midnight/noon/teatime */

    nowtimer = time(NULL);
    nowtime = *localtime(&nowtimer);
    mktime(&nowtime);

    runtime = nowtime;

    ret_code = 0;
    seconds_defined = 0;
    utc_defined = 0;

    init_scanner(token_nr, token_arr);

    switch (token()) {
        case NOW:
        case PLUS:
        case MINUS:
            plusminus(&runtime);
            break;
        case NUMBER:
            tod(&runtime);
            month(&runtime);
            break;

            /* evil coding for TEATIME|NOON|MIDNIGHT - we've initialised
             * hr to zero up above, then fall into this case in such a
             * way so we add +12 +4 hours to it for teatime, +12 hours
             * to it for noon, and nothing at all for midnight, then
             * set our runtime to that hour before leaping into the
             * month scanner
             */
        case TEATIME:
            hr += 4;
        case NOON:
            hr += 12;
        case MIDNIGHT:
            if (runtime.tm_hour >= hr) {
                runtime.tm_mday++;
                runtime.tm_wday++;
            }
            runtime.tm_hour = hr;
            runtime.tm_min = 0;
            token();
            /* FALLTHROUGH to month setting */
        default:
            month(&runtime);
            break;
    } /* ugly case statement */
    expect(EOF);

    /* convert back to time_t
    */
    runtime.tm_isdst = -1;
    runtimer = mktime(&runtime);

    // Account for DST
    if (utc_defined == 1 && runtime.tm_isdst == 1) {
        if (nowtime.tm_isdst == 1) {
            runtimer += 3600;
        } else if (nowtime.tm_isdst  == 0) {
            runtimer += 7200;
        }
    }

    if (runtimer < 0) {
        panic(GARBLED_TIME);
    }

    *result = runtimer;
    return ret_code;
} /* parsetime */

int main
(int argc, char **argv)
{
/* main function to build command-line binary for testing */
    int ret_code;
    time_t result;
    if (argc < 2) {
        usage();
    }

    ret_code = parsetime(argc-optind, argv+optind, &result);
    if (ret_code == 0) {
        printf("%s", ctime(&result));
    }
    return ret_code;
}
