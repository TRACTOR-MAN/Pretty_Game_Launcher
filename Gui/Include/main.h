#ifndef MAIN_H
#define MAIN_H

#include <QApplication>

enum application_themes_et
{
    LIGHT,
    DARK
};

class application_theme_c
{
public:
    application_theme_c( application_themes_et desired_initial_theme_e, QApplication &psd_application );
    ~application_theme_c( ){ }

    // Member function for setting up the theme
    void setupTheme ( application_themes_et desired_theeme_e );

    // The current theme
    application_themes_et current_theme_e;

private:
    QApplication &application;
};

#endif // MAIN_H
