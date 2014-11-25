#include <stdio.h>
#include <time.h>

#include "globals.h"

void write_log( char* msg, unsigned long value ) {

    FILE *fp;
    //char logfile[] = "Logfile.log";
    char logfile[100];
    sprintf(logfile, "drtt_log_%d.log", globals.src_node);
    time_t logtime;
    struct tm *logtm;

    logtime = time( NULL );
    logtm = localtime( &logtime );

    fp = fopen( logfile, "a" );

    if ( fp ) {
        fprintf(fp,"%04d-%02d-%02d %02d:%02d:%02d - %s : %lu \n", 1900 + logtm->tm_year, logtm->tm_mon + 1,
                logtm->tm_mday, logtm->tm_hour, logtm->tm_min, logtm->tm_sec ,
                msg, value );
        fclose(fp);

    } else {
        printf( "Error opening logfile %s\n", logfile );
    }
}
