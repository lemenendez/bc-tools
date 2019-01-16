#include <bc-tools.hpp>
#include <p-options.hpp>

int main(int argc, char *argv[]) 
{  
  po_wrapper o;
  std::string p_key;

  o.handle_po(argc, argv);
  o.get("pk",p_key);

  if(p_key.length()>0) {
    my_bc_tools bc_tool;
    if (bc_tool.setSecretKey(p_key.c_str()))  //038109007313a5807b2eccc082c8c3fbb988a973cacf1a7df9ce725c31b14776
    {
      bc_tool.printSecretKeyHex();
      bc_tool.printPublicKey();    
      bc_tool.printBitcoinAddress();
    } 
    else 
    {
      std::cout << "secret key is not valid" << std::endl;
    }
    return 0;
  }  

}