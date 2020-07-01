#ifndef MX_DEFINES_H
#define MX_DEFINES_H

#define MX_COUNT_FUCTIONS 16
#define MX_ERROR_THREAD stderr
#define MX_DATABASE "database/database.db"
#define MX_CREATE_DATABASE "database/create_db_in_c.sql"
#define MX_PORT_test 2365
#define MX_MAX_CONNECT 256
#define MX_THREAD 6
#define MX_MAX_SIZE_REQUEST 1024
/* 
* 0 bit of query
* Query Status
*/
enum e_status {
    MX_QS_ERR_FUNC = 100, // can't understand query
    MX_QS_ERR_REG = 101, // nickname for registration is busy
    MX_QS_ERR_SERV = 102, // server error
    MX_QS_ERR_RIGHT = 103, // error of rights(unregistered, not admin, not in chat ...)
    MX_QS_ERR_LOGIN = 104, // incorrect login or password
    MX_QS_ERR_LOG_MANY = 105, // to many accounts finded(2+) when login
    MX_QS_ERR_REQUEST = 106, // request error
    MQ_QS_NOT_FOUND = 107, //
    MQ_QS_ERR_SQL = 108, // error sql database

    MX_QS_OK = 200 // query successful
};
#endif
