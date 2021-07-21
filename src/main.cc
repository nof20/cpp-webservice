#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/core/macro/codegen.hpp"

// See https://oatpp.io/docs/start/step-by-step/

/** 
 * Custom Request Handler
 */
class Handler : public oatpp::web::server::HttpRequestHandler
{
public:
    /**
   * Handle incoming request and return outgoing response.
   */
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest> &request) override
    {
        return ResponseFactory::createResponse(Status::CODE_200, "Hello World!");
    }
};

/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Message Data-Transfer-Object
 */
class MessageDto : public oatpp::DTO
{

    DTO_INIT(MessageDto, DTO /* Extends */)

    DTO_FIELD(Int32, statusCode); // Status code field
    DTO_FIELD(String, message);   // Message field
};

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)

/**
 * Custom Request Handler
 */
class JsonHandler : public oatpp::web::server::HttpRequestHandler
{
private:
    std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;

public:
    /**
   * Constructor with object mapper.
   * @param objectMapper - object mapper used to serialize objects.
   */
    JsonHandler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper> &objectMapper)
        : m_objectMapper(objectMapper)
    {
    }

    /**
   * Handle incoming request and return outgoing response.
   */
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest> &request) override
    {
        auto message = MessageDto::createShared();
        message->statusCode = 1024;
        message->message = "Hello DTO!";
        return ResponseFactory::createResponse(Status::CODE_200, message, m_objectMapper);
    }
};

void run()
{

    /* Create json object mapper */
    auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

    /* Create Router for HTTP requests routing */
    auto router = oatpp::web::server::HttpRouter::createShared();

    /* Route GET - "/hello" requests to Handler */
    router->route("GET", "/hello", std::make_shared<Handler>());

    router->route("GET", "/helloJson", std::make_shared<JsonHandler>(objectMapper /* json object mapper */));

    /* Create HTTP connection handler with router */
    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    /* Create TCP connection provider */
    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"localhost", 8000, oatpp::network::Address::IP_4});

    /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
    oatpp::network::Server server(connectionProvider, connectionHandler);

    /* Priny info about server port */
    OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData());

    /* Run server */
    server.run();
}

int main()
{

    /* Init oatpp Environment */
    oatpp::base::Environment::init();

    /* Run App */
    run();

    /* Destroy oatpp Environment */
    oatpp::base::Environment::destroy();

    return 0;
}