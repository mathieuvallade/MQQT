#include <iostream>                                                                         
#include <mqtt/async_client.h>                                                           

const std::string SERVER_ADDRESS("broker.emqx.io:1883");                                    
const std::string CLIENT_ID("mathieu");                                                  
int main(int argc, char* argv[])
{
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);                                 
    mqtt::connect_options options;                                                         
    options.set_clean_session(true);                                                      

    try {
        mqtt::token_ptr conntok = client.connect(options);                                 
        conntok->wait();                                                                   

        std::string payload = "mathieu vallade";                                            
        mqtt::message_ptr pubmsg = mqtt::make_message("/ynov/bordeaux/", payload);          
        client.publish(pubmsg)->wait();                                                     

        client.disconnect()->wait();                                                       
    catch (const mqtt::exception& exc) {                                                    
        std::cerr << "Error: " << exc.what() << std::endl;                                  
        return 1;                                                                           

    std::cout << "Message published successfully!" << std::endl;                           

    return 0;                                                                              
}