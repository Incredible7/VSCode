#include "CONCURRENT.h"

// Use std::call_once() to implement thread-safe lazy
// initialization of data members of class X
class X {
  public:
    X(connection_info const &connection_details_)
        : connection_details(connection_details_) {}
    void send_data(data_packet const &data) {
        std::call_once(connection_init_flag, &X::open_connection, this);
        connection.send_data(data);
    }
    data_packet receive_data() {
        std::call_once(connection_init_flag, &X::open_connection, this);
        return connection.receive_data();
    }

  private:
    connection_info connection_details;
    connection_handle connection;
    std::once_flag connection_init_flag;
    void open_connection() {
        connection = connection_manager.open(connection_details);
    }
};