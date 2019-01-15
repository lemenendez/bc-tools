#include <boost/program_options.hpp>
#include <string>

namespace opt = boost::program_options;

class po_wrapper 
{
  opt::options_description *desc;
  opt::variables_map vm;
  public:
    po_wrapper();
    void get(std::string, std::string&);
    void handle_po(int, char *[]);
};

po_wrapper::po_wrapper() {
  desc = new opt::options_description("all");  
}

void po_wrapper::get(std::string name, std::string &value) 
{  
  if(vm.count(name)) 
    value = vm[name].as<std::string>();   
  else
    value = "";
}

void po_wrapper::handle_po(int argc, char *argv[]) 
{
  desc->add_options()
    ("help", "Print help message message")
    ("pk", opt::value<std::string>(),"Enter private key")    
    ;
  opt::store(opt::parse_command_line(argc, argv, *desc), vm);
  opt::notify(vm);
}
