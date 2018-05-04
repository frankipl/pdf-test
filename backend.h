#ifndef BACKEND_H
#define BACKEND_H

#include <QtCore>
#include "wkhtmltox/pdf.h"

class Backend:public QObject {
    Q_OBJECT
public:
    Backend();
public slots:
signals:
private slots:
    bool createPdf();
private:
    QTimer  *timer;
};

void progress_changed(wkhtmltopdf_converter * c, int p);
void phase_changed(wkhtmltopdf_converter * c);
void error(wkhtmltopdf_converter * c, const char * msg);
void warning(wkhtmltopdf_converter * c, const char * msg);

#endif // BACKEND_H
