typedef enum {
    CONNECTED, DISCONNECTED
} connection_event_type;

struct ConnectionOptions {
    String mqtt_server;
    int mqtt_server_port;
    String mqtt_username;
    String mqtt_password;
};

typedef void ConnectionStatusUpdateCallback(connection_event_type eventType);

class Connection {
public:
    Connection();
    Connection(ConnectionOptions, ConnectionStatusUpdateCallback);
    void ConnectionBegin();
    int SendDistanceData(double distanceCm);
    String QueryFirmwareVersion(String deviceId);
private:
    ConnectionOptions _options;
};


