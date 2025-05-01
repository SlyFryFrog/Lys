import lys.main.app;

int main()
{
    Lys::App app;

    app.init();
    app.process();
    app.destroy();
    
    return 0;
}