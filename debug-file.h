#include <fstream>
using namespace std;
class debug
{
    public:
           debug();
           ~debug();

           void debug_file_init();
           void write_to_file(const char * text_to_write);

    private:
};


debug::debug()
{
;
}

debug::~debug()
{
;
}

void debug::debug_file_init()
{
    ofstream db_file("debug.txt");
    if(db_file.is_open()){
        db_file << "************ Debug.txt opened. ****************" << "\n";
        db_file.close();
    }
    else
        db_file.close();
}

void debug::write_to_file(const char * text_to_write)
{
    ofstream db_file ("debug.txt" , ios::out | ios::app);
    if(db_file.is_open()){
        db_file << text_to_write << "\n";
        }
    else
        db_file.close();

    db_file.close();
}

