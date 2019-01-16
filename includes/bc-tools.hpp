#include <bitcoin/bitcoin.hpp>
#include <string>
#include <array>

using namespace bc;

class my_bc_tools 
{
  std::string my_secret_key;
  std::string bitcoin_address;

  ec_secret decoded_secret_ec;  

  wallet::ec_private secret_key;  
  wallet::ec_public public_key;  

  bool decodeSecret(std::string secret);

  public:
    std::string getSecretKey();
    ec_secret getDecodedSecretKey();
    bool setSecretKey(std::string secret);
    void printSecretKeyHex();
    void printPublicKey();    
    void printBitcoinAddress();
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
    secret_key = wallet::ec_private(decoded_secret_ec, wallet::ec_private::mainnet_p2kh);  // generate private key
    public_key = wallet::ec_public(secret_key); // generate public key
    bc::data_chunk public_key_data;
    public_key.to_data(public_key_data);

    const auto hash = bc::bitcoin_short_hash(public_key_data);  // hash
    bc::data_chunk unencoded_address;
    unencoded_address.reserve(25);
    unencoded_address.push_back(0);

     bc::extend_data(unencoded_address, hash); 
     bc::append_checksum(unencoded_address);
     bitcoin_address = bc::encode_base58(unencoded_address);

  }
  return decoded;
}

void my_bc_tools::printBitcoinAddress() {
  std::cout << bitcoin_address << std::endl; 
}

bool my_bc_tools::decodeSecret(std::string secret) { return decode_base16(decoded_secret_ec, secret ); }
