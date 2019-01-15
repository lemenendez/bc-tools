#include <bitcoin/bitcoin.hpp>
#include <string>
#include <array>

using namespace bc;

class my_bc_tools 
{
  std::string my_secret_key;
  ec_secret decoded_secret_ec;
  std::array<uint8_t, ec_secret_size> decoded_secret; // not needed, just an example
  
  wallet::ec_public public_key;

  bool decodeSecret(std::string secret);

  public:
    std::string getSecretKey();
    ec_secret getDecodedSecretKey();
    bool setSecretKey(std::string secret);
    void printSecretKeyHex();
    void printPublicKey();
};

void my_bc_tools::printSecretKeyHex() 
{  
  for (const auto& b: decoded_secret_ec)
    std::cout << std::hex << (0xFF & b) << ' ' ;
  std::cout << std::endl;  
}

void my_bc_tools::printPublicKey() 
{
  std::cout << public_key.encoded() << std::endl;
}

ec_secret my_bc_tools::getDecodedSecretKey() {  return decoded_secret_ec; }

std::string my_bc_tools::getSecretKey() { return my_secret_key; }

bool my_bc_tools::setSecretKey(std::string secret) 
{   
  
  if(secret.length()!=ec_secret_size * 2) return false;
  bool decoded = decodeSecret(secret);
  if(decoded) 
  {
    my_secret_key = secret;
    decoded_secret = decoded_secret_ec;
    public_key = wallet::ec_public(decoded_secret_ec); // generate public key
  }
  return decoded;
}

bool my_bc_tools::decodeSecret(std::string secret) { return decode_base16(decoded_secret, secret ); }
