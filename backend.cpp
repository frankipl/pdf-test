#include "backend.h"

Backend::Backend() {
    timer=new QTimer(this);
    timer->setInterval(2000);
    timer->setSingleShot(true);
    connect(timer,SIGNAL(timeout()),this,SLOT(createPdf()));
    timer->start();
}
bool Backend::createPdf() {
    wkhtmltopdf_global_settings * gs;
    wkhtmltopdf_object_settings * os;
    wkhtmltopdf_converter *c;

    /* Init wkhtmltopdf in graphics less mode */
    wkhtmltopdf_init(false);

    /*
         * Create a global settings object used to store options that are not
         * related to input objects, note that control of this object is parsed to
         * the converter later, which is then responsible for freeing it
         */
    gs = wkhtmltopdf_create_global_settings();
    /* We want the result to be storred in the file called test.pdf */
    wkhtmltopdf_set_global_setting(gs, "out", "test.pdf");

    wkhtmltopdf_set_global_setting(gs, "load.cookieJar", "myjar.jar");
    /*
         * Create a input object settings object that is used to store settings
         * related to a input object, note again that control of this object is parsed to
         * the converter later, which is then responsible for freeing it
         */
    os = wkhtmltopdf_create_object_settings();
    /* We want to convert to convert the qstring documentation page */
    wkhtmltopdf_set_object_setting(os, "page", "http://doc.qt.io/qt-5/qstring.html");
    //wkhtmltopdf_set_object_setting(os, "page", "test.txt");

    /* Create the actual converter object used to convert the pages */
    c = wkhtmltopdf_create_converter(gs);

    /* Call the progress_changed function when progress changes */
    wkhtmltopdf_set_progress_changed_callback(c, progress_changed);

    /* Call the phase _changed function when the phase changes */
    wkhtmltopdf_set_phase_changed_callback(c, phase_changed);

    /* Call the error function when an error occurs */
    wkhtmltopdf_set_error_callback(c, error);

    /* Call the warning function when a warning is issued */
    wkhtmltopdf_set_warning_callback(c, warning);

    /*
         * Add the the settings object describing the qstring documentation page
         * to the list of pages to convert. Objects are converted in the order in which
         * they are added
         */
    wkhtmltopdf_add_object(c, os, NULL);

    /* Perform the actual conversion */
    if (!wkhtmltopdf_convert(c))
        fprintf(stderr, "Conversion failed!");

    /* Output possible http error code encountered */
    printf("httpErrorCode: %d\n", wkhtmltopdf_http_error_code(c));

    /* Destroy the converter object since we are done with it */
    wkhtmltopdf_destroy_converter(c);

    /* We will no longer be needing wkhtmltopdf funcionality */
    wkhtmltopdf_deinit();

    qDebug()<<"Done.";
    return 0;
}
void progress_changed(wkhtmltopdf_converter * c, int p) {
    printf("%3d%%\r",p);
    fflush(stdout);
}
/* Print loading phase information */
void phase_changed(wkhtmltopdf_converter * c) {
    int phase = wkhtmltopdf_current_phase(c);
    printf("%s\n", wkhtmltopdf_phase_description(c, phase));
}

/* Print a message to stderr when an error occurs */
void error(wkhtmltopdf_converter * c, const char * msg) {
    fprintf(stderr, "Error: %s\n", msg);
}

/* Print a message to stderr when a warning is issued */
void warning(wkhtmltopdf_converter * c, const char * msg) {
    fprintf(stderr, "Warning: %s\n", msg);
}
