#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <nanogui/nanogui.h>
#pragma GCC diagnostic pop

#include "config.h"
#include "job.h"
#include "receipent.h"

#include "database_handler.h"
#include "mail_handler.h"
#include "csv_utils.h"

using namespace std;
using namespace nanogui;

enum test_enum
{
    Item1 = 0,
    Item2,
    Item3
};

bool bvar = true;
int ivar = 12345678;
double dvar = 3.1415926;
float fvar = (float)dvar;
std::string strval = "A string";
std::string strval2 = "";
test_enum enumval = Item2;
Color colval(0.5f, 0.5f, 0.7f, 1.f);

int main()
{
    MailHandler mailer{"host", 443, "user", "pw"};
    DatabaseHandler db{};

    

    nanogui::init();

    Screen *screen = new Screen(Vector2i(500, 700), "NanoGUI test");

    bool enabled = true;
    FormHelper *gui = new FormHelper(screen);
    nanogui::ref<Window> window = gui->add_window(Vector2i(10, 10), "Form helper example");
     window->set_layout(new GroupLayout());

    /*Window *window = new Window(screen, "Button demo");
    window->set_position(Vector2i(15, 15));
    window->set_layout(new GroupLayout());*/

    Button *b = new Button(window, "Plain button");
    b->set_callback([] { std::cout << "pushed!" << std::endl; });
    b->set_tooltip("short tooltip");

    gui->add_group("Basic types");
    gui->add_variable("bool", bvar);
    gui->add_variable("string", strval);
    gui->add_variable("placeholder", strval2)->set_placeholder("placeholder");

    gui->add_group("Validating fields");
    gui->add_variable("int", ivar)->set_spinnable(true);
    gui->add_variable("float", fvar);
    gui->add_variable("double", dvar)->set_spinnable(true);

    gui->add_group("Complex types");
    gui->add_variable("Enumeration", enumval, enabled)
        ->set_items({"Item 1", "Item 2", "Item 3"});
    gui->add_variable("Color", colval);

    gui->add_group("Other widgets");
    gui->add_button("A button", []() { std::cout << "Button pressed." << std::endl; });

    screen->set_visible(true);
    screen->perform_layout();
    window->center();

    nanogui::mainloop(-1);

    nanogui::shutdown();
    return 0;
}
