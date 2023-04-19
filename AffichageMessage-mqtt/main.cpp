#include <iostream>
#include <mqtt/async_client.h>

using namespace std;

const string s_ADDRESS{"tcp://broker.emqx.io:1883"};
const string s_CLIENT_ID{"MQTT-Receiver"};
const string s_TOPIC{"/ynov/bordeaux/"};

class Callback : public virtual mqtt::callback
{
public:
    void message_arrived(mqtt::const_message_ptr msg) override
    {
        cout << "Message received on topic " << msg->get_topic() << endl;
        cout << "Message content: " << msg->to_string() << endl;
    }

    virtual void connection_lost(const string &cause) override
    {
        cout << "\nConnection lost" << endl;
        if (!cause.empty())
            cout << "\tcause: " << cause << endl;
    }
};

int main()
{
    mqtt::async_client client(s_ADDRESS, s_CLIENT_ID);
    try
    {
        mqtt::connect_options conn_opts;
        conn_opts.set_clean_session(true);

        Callback callback;
        client.set_callback(callback);

        client.connect(conn_opts)->wait();

        mqtt::topic mqtt_topic(client, s_TOPIC, 0);
        mqtt_topic.subscribe()->wait();

        while (true)
        {
            // Waiting for messages
        }
    }
    catch (const mqtt::exception &exc)
    {
        client.disconnect()->wait();
        cerr << "MQTT error: " << exc.what() << endl;
        return 1;
    }

    return 0;
}