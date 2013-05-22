
namespace
{
class ConnectionHandler
{
    bool is_conn_close_;
    Connection* conn_;
public:

    ConnectionHandler(Connection* conn):
        conn_(conn),
        is_conn_close_(false){}
        
    void Close()
    {
        try{
            conn_ -> close();
        }
        catch(...){
            //...
        }        
        is_conn_close_ = true;
    }
    
    operator Connection*()const
    {
        return conn_;
    }
    
    ~ConnectionHandler()
    {
        if(!is_conn_close_){
            Close();
        }
    }
        
private://nocopyable
    ConnectionHandler(const ConnectionHandler&);
    ConnectionHandler& operator=(const ConnectionHandler&);
};//class ConnectionHandler

}

int main()
{
    Driver *driver = get_driver_instance();
    ConnectionHandler conn(driver -> connect("..."));
    //do something
    return 0;
}