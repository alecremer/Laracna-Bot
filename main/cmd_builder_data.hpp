#ifndef CmdBuilderData_HPP
#define CmdBuilderData_HPP

class CmdBuilderData
{
private:

    char* command;
    
public:
    
    char** argv;
    int argc;

    CmdBuilderData(void){}

};

#endif