#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 2 "parsetime.y"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parsetime.h"
#include "panic.h"

#define YYDEBUG 1

struct tm exectm;
static int isgmt;
static int yearspec;
static int time_only;

extern int yyerror(char *s);
extern int yylex();

int add_date(float number, int period);
#line 22 "parsetime.y"
typedef union {
    char *  charval;
    int     intval;
    float   floatval;
} YYSTYPE;
#line 48 "y.tab.c"
#define DOTTEDDATE 257
#define HYPHENDATE 258
#define HOURMIN 259
#define INT1DIGIT 260
#define INT2DIGIT 261
#define INT4DIGIT 262
#define INT5_8DIGIT 263
#define INT 264
#define FLOAT 265
#define NOW 266
#define AM 267
#define PM 268
#define NOON 269
#define MIDNIGHT 270
#define TEATIME 271
#define SUN 272
#define MON 273
#define TUE 274
#define WED 275
#define THU 276
#define FRI 277
#define SAT 278
#define TODAY 279
#define TOMORROW 280
#define NEXT 281
#define MINUTE 282
#define HOUR 283
#define DAY 284
#define WEEK 285
#define MONTH 286
#define YEAR 287
#define JAN 288
#define FEB 289
#define MAR 290
#define APR 291
#define MAY 292
#define JUN 293
#define JUL 294
#define AUG 295
#define SEP 296
#define OCT 297
#define NOV 298
#define DEC 299
#define UTC 300
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    0,   10,   10,   10,   10,   13,   13,   14,
   14,   14,   14,   14,   14,   14,    2,   16,   18,   17,
   17,   15,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,    1,   19,   19,   19,
   19,   19,   19,   19,   19,   19,   19,   19,   19,   22,
   20,   21,    9,    9,    9,    9,    9,    9,    9,   11,
   11,   23,   24,    8,    7,    7,    7,    7,    7,    7,
    3,    3,    4,    4,    5,    5,    5,    5,    5,    6,
    6,
};
short yylen[] = {                                         2,
    1,    2,    2,    1,    1,    2,    1,    1,    2,    1,
    2,    1,    2,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    2,    3,    4,    1,    1,    1,    1,    1,
    2,    3,    5,    1,    2,    2,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    3,    3,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,
};
short yydefred[] = {                                      0,
    0,   30,   29,   19,   71,   72,   17,   37,    7,   14,
   15,   16,   53,   54,   55,   56,   57,   58,   59,   27,
   28,    0,   38,   39,   40,   41,   42,   43,   44,   45,
   46,   47,   48,   49,    0,   34,   10,    0,   26,    0,
    4,    0,    0,    0,    0,    0,    0,    0,    3,   65,
   66,   67,   68,   69,   70,   35,   36,    0,    0,    2,
   60,   61,    0,    6,   22,    9,   20,   21,   11,   13,
   51,    0,    0,    0,   76,   77,   78,   79,   75,   81,
   80,   64,    0,    0,   73,   74,    0,   52,   24,   32,
    0,   62,   63,   25,    0,   33,
};
short yydgoto[] = {                                      35,
   36,   37,   71,   88,   81,   82,   56,   83,   39,   40,
   60,   41,   42,   43,   66,   44,   69,   45,   46,   47,
   89,   48,   61,   62,
};
short yysindex[] = {                                   -197,
   33,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -263,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -27,
    0, -152, -244, -241, -241, -232, -257,   20,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -148, -148,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -39, -207, -232,    0,    0,    0,    0,    0,    0,
    0,    0, -134, -134,    0,    0, -207,    0,    0,    0,
   21,    0,    0,    0, -207,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -47,    0,   70,
    0,    4,   45,    0,    1,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   57,    0,    0,    0,    0,    0,    0,    0,
    0,    7,    8,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,    0,    6,    0,    0,    0,  -26,   12,   63,    0,
    0,   44,    0,    0,    0,    0,   42,    0,   56,  -44,
  -70,    0,    0,    0,
};
#define YYTABLESIZE 356
short yytable[] = {                                      50,
   12,   72,   90,    5,   87,   38,   23,   31,   13,   14,
   15,   16,   17,   18,   19,   58,   94,   59,   50,   51,
   52,   53,   54,   55,   96,   67,   68,    5,    6,   91,
   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
   33,   34,   49,   12,    8,   12,    5,   63,    5,   23,
   31,   23,   31,   85,   86,   65,   92,   93,    1,    2,
    3,    4,    5,    6,    7,    8,   74,   95,    9,    1,
   84,   10,   11,   12,   13,   14,   15,   16,   17,   18,
   19,   20,   21,   22,   57,   64,   70,    8,    0,    8,
   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
   33,   34,   73,   50,    2,    3,    0,    5,    6,    0,
    8,   75,   76,   77,   78,   79,   80,    0,    0,   13,
   14,   15,   16,   17,   18,   19,   20,   21,   22,    0,
    0,    0,    0,    0,    0,   23,   24,   25,   26,   27,
   28,   29,   30,   31,   32,   33,   34,   50,   51,   52,
   53,   54,   55,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   18,
   18,   85,   86,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   51,   51,   51,   51,   51,   51,   51,   51,   51,   51,
   51,   51,    0,    0,    0,    0,    0,   12,   12,    0,
   12,   12,    0,   12,    0,    0,    0,    0,    0,    0,
    0,    0,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,    0,    0,    0,    0,    0,    0,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,    8,    8,    0,    8,    8,    0,    8,    0,    0,
    0,    0,    0,    0,    0,    0,    8,    8,    8,    8,
    8,    8,    8,    8,    8,    8,    0,    0,    0,    0,
    0,    0,    8,    8,    8,    8,    8,    8,    8,    8,
    8,    8,    8,    8,   51,   51,   51,   51,   51,   51,
   51,   51,   51,   51,   51,   51,
};
short yycheck[] = {                                      47,
    0,   46,   73,    0,   44,    0,    0,    0,  272,  273,
  274,  275,  276,  277,  278,   43,   87,   45,  282,  283,
  284,  285,  286,  287,   95,  267,  268,  260,  261,   74,
  288,  289,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  299,   10,   43,    0,   45,   43,   42,   45,   43,
   43,   45,   45,  261,  262,  300,   83,   84,  256,  257,
  258,  259,  260,  261,  262,  263,   47,   47,  266,    0,
   59,  269,  270,  271,  272,  273,  274,  275,  276,  277,
  278,  279,  280,  281,   22,   42,   45,   43,   -1,   45,
  288,  289,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  299,   47,   47,  257,  258,   -1,  260,  261,   -1,
  263,  260,  261,  262,  263,  264,  265,   -1,   -1,  272,
  273,  274,  275,  276,  277,  278,  279,  280,  281,   -1,
   -1,   -1,   -1,   -1,   -1,  288,  289,  290,  291,  292,
  293,  294,  295,  296,  297,  298,  299,  282,  283,  284,
  285,  286,  287,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  267,
  268,  261,  262,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  288,  289,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  299,   -1,   -1,   -1,   -1,   -1,  257,  258,   -1,
  260,  261,   -1,  263,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  272,  273,  274,  275,  276,  277,  278,  279,
  280,  281,   -1,   -1,   -1,   -1,   -1,   -1,  288,  289,
  290,  291,  292,  293,  294,  295,  296,  297,  298,  299,
  300,  257,  258,   -1,  260,  261,   -1,  263,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  272,  273,  274,  275,
  276,  277,  278,  279,  280,  281,   -1,   -1,   -1,   -1,
   -1,   -1,  288,  289,  290,  291,  292,  293,  294,  295,
  296,  297,  298,  299,  288,  289,  290,  291,  292,  293,
  294,  295,  296,  297,  298,  299,
};
#define YYFINAL 35
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 300
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,"'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"DOTTEDDATE","HYPHENDATE","HOURMIN","INT1DIGIT","INT2DIGIT","INT4DIGIT",
"INT5_8DIGIT","INT","FLOAT","NOW","AM","PM","NOON","MIDNIGHT","TEATIME","SUN",
"MON","TUE","WED","THU","FRI","SAT","TODAY","TOMORROW","NEXT","MINUTE","HOUR",
"DAY","WEEK","MONTH","YEAR","JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG",
"SEP","OCT","NOV","DEC","UTC",
};
char *yyrule[] = {
"$accept : timespec",
"timespec : spec_base",
"timespec : spec_base inc_or_dec",
"timespec : error '\\n'",
"spec_base : date",
"spec_base : time",
"spec_base : time date",
"spec_base : NOW",
"time : time_base",
"time : time_base timezone_name",
"time_base : hr24clock_hr_min",
"time_base : time_hour am_pm",
"time_base : time_hour_min",
"time_base : time_hour_min am_pm",
"time_base : NOON",
"time_base : MIDNIGHT",
"time_base : TEATIME",
"hr24clock_hr_min : INT4DIGIT",
"time_hour : int1_2digit",
"time_hour_min : HOURMIN",
"am_pm : AM",
"am_pm : PM",
"timezone_name : UTC",
"date : month_name day_number",
"date : month_name day_number year_number",
"date : month_name day_number ',' year_number",
"date : day_of_week",
"date : TODAY",
"date : TOMORROW",
"date : HYPHENDATE",
"date : DOTTEDDATE",
"date : day_number month_name",
"date : day_number month_name year_number",
"date : month_number '/' day_number '/' year_number",
"date : concatenated_date",
"date : NEXT inc_dec_period",
"date : NEXT day_of_week",
"concatenated_date : INT5_8DIGIT",
"month_name : JAN",
"month_name : FEB",
"month_name : MAR",
"month_name : APR",
"month_name : MAY",
"month_name : JUN",
"month_name : JUL",
"month_name : AUG",
"month_name : SEP",
"month_name : OCT",
"month_name : NOV",
"month_name : DEC",
"month_number : int1_2digit",
"day_number : int1_2digit",
"year_number : int2_or_4digit",
"day_of_week : SUN",
"day_of_week : MON",
"day_of_week : TUE",
"day_of_week : WED",
"day_of_week : THU",
"day_of_week : FRI",
"day_of_week : SAT",
"inc_or_dec : increment",
"inc_or_dec : decrement",
"increment : '+' inc_dec_number inc_dec_period",
"decrement : '-' inc_dec_number inc_dec_period",
"inc_dec_number : floating",
"inc_dec_period : MINUTE",
"inc_dec_period : HOUR",
"inc_dec_period : DAY",
"inc_dec_period : WEEK",
"inc_dec_period : MONTH",
"inc_dec_period : YEAR",
"int1_2digit : INT1DIGIT",
"int1_2digit : INT2DIGIT",
"int2_or_4digit : INT2DIGIT",
"int2_or_4digit : INT4DIGIT",
"integer : INT",
"integer : INT1DIGIT",
"integer : INT2DIGIT",
"integer : INT4DIGIT",
"integer : INT5_8DIGIT",
"floating : integer",
"floating : FLOAT",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 497 "parsetime.y"


time_t parsetime(time_t, int, char **);

time_t
parsetime(time_t currtime, int argc, char **argv)
{
    time_t exectime;
    struct tm currtm;

    my_argv = argv;
    exectm = *localtime(&currtime);
    currtime -= exectm.tm_sec;
    exectm.tm_sec = 0;
    exectm.tm_isdst = -1;
    memcpy(&currtm,&exectm,sizeof(currtm));
    time_only = 0;
    yearspec = 0;

    if (yyparse() == 0) {
        if (time_only)
        {
            if (exectm.tm_mday == currtm.tm_mday &&
                (exectm.tm_hour < currtm.tm_hour ||
                 (exectm.tm_hour == currtm.tm_hour &&
                  exectm.tm_min <= currtm.tm_min)))
            {
                exectm.tm_mday++;
            }
        }
        else if (!yearspec) {
            if (exectm.tm_year == currtm.tm_year &&
                (exectm.tm_mon < currtm.tm_mon ||
                 (exectm.tm_mon == currtm.tm_mon &&
                  exectm.tm_mday < currtm.tm_mday)))
            exectm.tm_year++;
        }

        exectime = mktime(&exectm);
        if (exectime == (time_t)-1)
            return 0;
        if (isgmt) {
            exectime -= timezone;
            if (currtm.tm_isdst && !exectm.tm_isdst)
            exectime -= 3600;
        }
        // if (exectime < currtime)
        //  panic("refusing to create job destined in the past");
        return exectime;
    }
    else {
    return 0;
    }
}

#ifdef TEST_PARSER

int
main(int argc, char **argv)
{
    int retval = 1;
    time_t res;
    time_t currtime;

    if (argc < 3) {
        fprintf(stderr, "usage: parsetest [now] [timespec] ...\n");
        exit(EXIT_FAILURE);
    }

    currtime = atoll(argv[1]);
    res = parsetime(currtime, argc-2, argv + 2);
    if (res > 0) {
        printf("%s",ctime(&res));
        retval = 0;
    }
    else {
        printf("Ooops...\n");
        retval = 1;
    }
    return retval;
}

void
panic(char *a)
{
    fputs(a, stderr);
    exit(EXIT_FAILURE);
}
#endif

int yyerror(char *s)
{
    if (last_token == NULL)
    {
        last_token = "(empty)";
    }
    fprintf(stderr,"%s. Last token seen: %s\n",s, last_token);
    return 0;
}

void
add_seconds(struct tm *tm, long numsec)
{
    struct tm basetm = *tm;
    time_t timeval;

    timeval = mktime(tm);
    if (timeval == (time_t)-1)
        timeval = (time_t)0;
    timeval += numsec;
    *tm = *localtime(&timeval);

    /*
     * Adjust +-1 hour when moving in or out of DST
     */

    if (daylight > 0)   /* Only check if DST is used here */
    {
        /* Set tm_isdst on &basetm and tm */
        (void) mktime(&basetm);
        (void) mktime(tm);

        if (basetm.tm_isdst > 0 && tm->tm_isdst < 1)
        {   /* DST to no DST */
            timeval += 3600l;
            *tm = *localtime(&timeval);
        }
        else if (basetm.tm_isdst < 1 && tm->tm_isdst > 0)
        {   /* no DST to DST */
            timeval -= 3600l;
            *tm = *localtime(&timeval);
        }
    }
}

int
add_date(float number, int period)
{
    printf("%f", number);
    switch(period) {
    case MINUTE:
        add_seconds(&exectm , 60l*number);
        break;

    case HOUR:
        add_seconds(&exectm, 3600l * number);
        break;

    case DAY:
        add_seconds(&exectm, 24*3600l * number);
        break;

    case WEEK:
        add_seconds(&exectm, 7*24*3600l*number);
        break;

    case MONTH:
    {
        int wholemonths = number;
        float partialmonth = number - wholemonths;
        int newmonth = exectm.tm_mon + wholemonths;
        wholemonths= 0;
        while (newmonth < 0) {
            newmonth += 12;
            wholemonths--;
        }
        exectm.tm_mon = newmonth % 12;
        wholemonths += newmonth / 12 ;
        number = wholemonths;

        add_seconds(&exectm, 30*24*3600l*partialmonth);
        /* Recalculate tm_isdst so we don't get a +-1 hour creep */
        exectm.tm_isdst = -1;
        (void) mktime(&exectm);
    }
    if (number == 0) {
        break;
    }
    /* fall through */

    case YEAR:
    {
        int wholeyears = number;
        float partialyear = number - wholeyears;

        exectm.tm_year += wholeyears;
        add_seconds(&exectm, 365*24*3600l*partialyear);
        /* Recalculate tm_isdst so we don't get a +-1 hour creep */
        exectm.tm_isdst = -1;
        (void) mktime(&exectm);
        break;
    }

    default:
        yyerror("Internal parser error");
        fprintf(stderr,"Unexpected case %d\n", period);
        abort();
    }

    return 0;
}
#line 579 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 5:
#line 68 "parsetime.y"
{
        time_only = 1;
    }
break;
case 7:
#line 73 "parsetime.y"
{
        yearspec = 1;
    }
break;
case 10:
#line 85 "parsetime.y"
{
        exectm.tm_min = -1;
        exectm.tm_hour = -1;
        sscanf(yyvsp[0].charval, "%2d %2d", &exectm.tm_hour,
            &exectm.tm_min);
        free(yyvsp[0].charval);

        if (exectm.tm_min > 60 || exectm.tm_min < 0) {
            yyerror("Problem in minutes specification");
            YYERROR;
        }
        if (exectm.tm_hour > 24 || exectm.tm_hour < 0) {
            yyerror("Problem in hours specification");
            YYERROR;
        }
    }
break;
case 14:
#line 105 "parsetime.y"
{
        exectm.tm_hour = 12;
        exectm.tm_min = 0;
    }
break;
case 15:
#line 110 "parsetime.y"
{
        exectm.tm_hour = 0;
        exectm.tm_min = 0;
    }
break;
case 16:
#line 115 "parsetime.y"
{
        exectm.tm_hour = 16;
        exectm.tm_min = 0;
    }
break;
case 18:
#line 127 "parsetime.y"
{
        sscanf(yyvsp[0].charval, "%d", &exectm.tm_hour);
        exectm.tm_min = 0;
        free(yyvsp[0].charval);

        if (exectm.tm_hour > 24 || exectm.tm_hour < 0) {
            yyerror("Problem in hours specification");
            YYERROR;
        }
    }
break;
case 19:
#line 141 "parsetime.y"
{
        exectm.tm_min = -1;
        exectm.tm_hour = -1;
        sscanf(yyvsp[0].charval, "%d %*c %d", &exectm.tm_hour,
            &exectm.tm_min);
        free(yyvsp[0].charval);

        if (exectm.tm_min > 60 || exectm.tm_min < 0) {
            yyerror("Problem in minutes specification");
            YYERROR;
        }
        if (exectm.tm_hour > 24 || exectm.tm_hour < 0) {
            yyerror("Problem in hours specification");
            YYERROR;
        }
    }
break;
case 20:
#line 161 "parsetime.y"
{
        if (exectm.tm_hour > 12) {
            yyerror("Hour too large for AM");
            YYERROR;
        }
        else if (exectm.tm_hour == 12) {
            exectm.tm_hour = 0;
        }
    }
break;
case 21:
#line 171 "parsetime.y"
{
        if (exectm.tm_hour > 12) {
            yyerror("Hour too large for PM");
            YYERROR;
        }
        else if (exectm.tm_hour < 12) {
            exectm.tm_hour +=12;
        }
    }
break;
case 22:
#line 184 "parsetime.y"
{
        isgmt = 1;
    }
break;
case 26:
#line 194 "parsetime.y"
{
        add_date ((6 + yyvsp[0].intval - exectm.tm_wday) %7 + 1, DAY);
    }
break;
case 28:
#line 199 "parsetime.y"
{
        add_date(1, DAY);
    }
break;
case 29:
#line 203 "parsetime.y"
{
        int ynum = -1;
        int mnum = -1;
        int dnum = -1;

        yearspec = 1;
        if (sscanf(yyvsp[0].charval, "%d %*c %d %*c %d",
            &ynum, &mnum, &dnum) != 3) {
            yyerror("Error in hypenated date");
            YYERROR;
        }

        if (mnum < 1 || mnum > 12) {
            yyerror("Error in month number");
            YYERROR;
        }
        exectm.tm_mon = mnum -1;

        if (ynum < 70) {
            ynum += 100;
        }
        else if (ynum > 1900) {
            ynum -= 1900;
        }
        exectm.tm_year = ynum ;

        if (dnum < 1
            || ((mnum ==  1 || mnum ==  3 || mnum ==  5 ||
                    mnum ==  7 || mnum ==  8 || mnum == 10 ||
                    mnum == 12) && dnum > 31)
            || ((mnum ==  4 || mnum ==  6 || mnum ==  9 ||
                    mnum == 11) && dnum > 30)
            || (mnum ==  2 && dnum > 29 &&
                __isleap(ynum+1900))
            || (mnum ==  2 && dnum > 28 &&
                !__isleap(ynum+1900))) {
            yyerror("Error in day of month");
            YYERROR;
        }
        exectm.tm_mday = dnum;

        free(yyvsp[0].charval);
    }
break;
case 30:
#line 247 "parsetime.y"
{
        int ynum = -1;
        int mnum = -1;
        int dnum = -1;

        yearspec = 1;

        if (sscanf(yyvsp[0].charval, "%d %*c %d %*c %d",
            &dnum, &mnum, &ynum) != 3) {
            yyerror("Error in dotted date");
            YYERROR;
        }

        if (mnum < 1 || mnum > 12) {
            yyerror("Error in month number");
            YYERROR;
        }
        exectm.tm_mon = mnum -1;

        if (ynum < 70) {
            ynum += 100;
        }
        else if (ynum > 1900) {
            ynum -= 1900;
        }
        exectm.tm_year = ynum ;

        if (dnum < 1
            || ((mnum ==  1 || mnum ==  3 || mnum ==  5 ||
                    mnum ==  7 || mnum ==  8 || mnum == 10 ||
                    mnum == 12) && dnum > 31)
            || ((mnum ==  4 || mnum ==  6 || mnum ==  9 ||
                    mnum == 11) && dnum > 30)
            || (mnum ==  2 && dnum > 29 &&  __isleap(ynum+1900))
            || (mnum ==  2 && dnum > 28 && !__isleap(ynum+1900))) {
            yyerror("Error in day of month");
            YYERROR; 
        }
        exectm.tm_mday = dnum;

        free(yyvsp[0].charval);
    }
break;
case 34:
#line 293 "parsetime.y"
{
        /* Ok, this is a kluge.  I hate design errors...  -Joey */
        char shallot[5];
        char *onion;

        yearspec = 1;
        onion=yyvsp[0].charval;
        memset (shallot, 0, sizeof (shallot));
        if (strlen(yyvsp[0].charval) == 5 || strlen(yyvsp[0].charval) == 7) {
            strncpy (shallot,onion,1);
            onion++;
        } else {
            strncpy (shallot,onion,2);
            onion+=2;
        }
        sscanf(shallot, "%d", &exectm.tm_mon);

        if (exectm.tm_mon < 1 || exectm.tm_mon > 12) {
            yyerror("Error in month number");
            YYERROR;
        }
        exectm.tm_mon--;

        memset (shallot, 0, sizeof (shallot));
        strncpy (shallot,onion,2);
            sscanf(shallot, "%d", &exectm.tm_mday);
        if (exectm.tm_mday < 0 || exectm.tm_mday > 31) {
            yyerror("Error in day of month");
            YYERROR;
        }

        onion+=2;
        memset (shallot, 0, sizeof (shallot));
        strncpy (shallot,onion,4);
        if ( sscanf(shallot, "%d", &exectm.tm_year) != 1) {
            yyerror("Error in year");
            YYERROR;
        }
        if (exectm.tm_year < 70) {
            exectm.tm_year += 100;
        }
        else if (exectm.tm_year > 1900) {
            exectm.tm_year -= 1900;
        }

        free (yyvsp[0].charval);
    }
break;
case 35:
#line 341 "parsetime.y"
{
        add_date(1, yyvsp[0].floatval);
    }
break;
case 36:
#line 345 "parsetime.y"
{
        add_date ((6 + yyvsp[0].intval - exectm.tm_wday) %7 +1, DAY);
    }
break;
case 38:
#line 355 "parsetime.y"
{ exectm.tm_mon = 0; }
break;
case 39:
#line 356 "parsetime.y"
{ exectm.tm_mon = 1; }
break;
case 40:
#line 357 "parsetime.y"
{ exectm.tm_mon = 2; }
break;
case 41:
#line 358 "parsetime.y"
{ exectm.tm_mon = 3; }
break;
case 42:
#line 359 "parsetime.y"
{ exectm.tm_mon = 4; }
break;
case 43:
#line 360 "parsetime.y"
{ exectm.tm_mon = 5; }
break;
case 44:
#line 361 "parsetime.y"
{ exectm.tm_mon = 6; }
break;
case 45:
#line 362 "parsetime.y"
{ exectm.tm_mon = 7; }
break;
case 46:
#line 363 "parsetime.y"
{ exectm.tm_mon = 8; }
break;
case 47:
#line 364 "parsetime.y"
{ exectm.tm_mon = 9; }
break;
case 48:
#line 365 "parsetime.y"
{ exectm.tm_mon =10; }
break;
case 49:
#line 366 "parsetime.y"
{ exectm.tm_mon =11; }
break;
case 50:
#line 371 "parsetime.y"
{
        {
            int mnum = -1;
            sscanf(yyvsp[0].charval, "%d", &mnum);

            if (mnum < 1 || mnum > 12) {
                yyerror("Error in month number");
                YYERROR;
            }
            exectm.tm_mon = mnum -1;
            free(yyvsp[0].charval);
        }
    }
break;
case 51:
#line 388 "parsetime.y"
{
        exectm.tm_mday = -1;
        sscanf(yyvsp[0].charval, "%d", &exectm.tm_mday);
        if (exectm.tm_mday < 1 || exectm.tm_mday > 31)
        {
            yyerror("Error in day of month");
            YYERROR; 
        }
        free(yyvsp[0].charval);
    }
break;
case 52:
#line 402 "parsetime.y"
{
        yearspec = 1;
        {
        int ynum;

        if ( sscanf(yyvsp[0].charval, "%d", &ynum) != 1) {
            yyerror("Error in year");
            YYERROR;
        }
        if (ynum < 70) {
            ynum += 100;
        }
        else if (ynum > 1900) {
            ynum -= 1900;
        }

        exectm.tm_year = ynum ;
        free(yyvsp[0].charval);
        }
    }
break;
case 53:
#line 425 "parsetime.y"
{ yyval.intval = 0; }
break;
case 54:
#line 426 "parsetime.y"
{ yyval.intval = 1; }
break;
case 55:
#line 427 "parsetime.y"
{ yyval.intval = 2; }
break;
case 56:
#line 428 "parsetime.y"
{ yyval.intval = 3; }
break;
case 57:
#line 429 "parsetime.y"
{ yyval.intval = 4; }
break;
case 58:
#line 430 "parsetime.y"
{ yyval.intval = 5; }
break;
case 59:
#line 431 "parsetime.y"
{ yyval.intval = 6; }
break;
case 62:
#line 441 "parsetime.y"
{
        add_date(yyvsp[-1].floatval, yyvsp[0].floatval);
    }
break;
case 63:
#line 448 "parsetime.y"
{
        add_date(-yyvsp[-1].floatval, yyvsp[0].floatval);
    }
break;
case 64:
#line 455 "parsetime.y"
{
        if (sscanf(yyvsp[0].charval, "%f", &yyval.floatval) != 1) {
            yyerror("Unknown increment");
            YYERROR;
        }
    free(yyvsp[0].charval);
    }
break;
case 65:
#line 465 "parsetime.y"
{ yyval.floatval = MINUTE; }
break;
case 66:
#line 466 "parsetime.y"
{ yyval.floatval = HOUR; }
break;
case 67:
#line 467 "parsetime.y"
{ yyval.floatval = DAY; time_only = 0; }
break;
case 68:
#line 468 "parsetime.y"
{ yyval.floatval = WEEK; time_only = 0; }
break;
case 69:
#line 469 "parsetime.y"
{ yyval.floatval = MONTH; time_only = 0; }
break;
case 70:
#line 470 "parsetime.y"
{ yyval.floatval = YEAR; time_only = 0; }
break;
#line 1213 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
