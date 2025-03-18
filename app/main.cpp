#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <NetworkManager.h>

using namespace boost::asio;
using boost::asio::ip::tcp;

const std::string WEB_ROOT = "../webapp"; // Set your webapp directory

void handle_request(tcp::socket& socket) {
    boost::system::error_code error;

    // Read HTTP request
    char buffer[1024];
    size_t bytes = socket.read_some(boost::asio::buffer(buffer), error);

    if (error && error != boost::asio::error::eof) {
        std::cerr << "Read error: " << error.message() << std::endl;
        return;
    }

    std::string request(buffer, bytes);
    std::cout << "Received Request:\n" << request << std::endl;

    // Parse the first line of the request
    std::istringstream request_stream(request);
    std::string method, url, http_version;
    request_stream >> method >> url >> http_version;

    // Default to serving index.html if no file is specified
    if (url == "/") {
        url = "/app.html";
    }

    // Build full file path
    std::string file_path = WEB_ROOT + url;

    if (!boost::filesystem::exists(file_path)) {
        std::string not_found = "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\n404 Not Found";
        boost::asio::write(socket, boost::asio::buffer(not_found));
        return;
    }

    // Read the file
    std::ifstream file(file_path, std::ios::binary);
    std::ostringstream file_content;
    file_content << file.rdbuf();
    std::string response_body = file_content.str();

    std::string content_type = "text/plain"; // Default

    if (url.ends_with(".html")) content_type = "text/html";
    if (url.ends_with(".css")) content_type = "text/css";
    if (url.ends_with(".js")) content_type = "application/javascript";
    if (url.ends_with(".wasm")) content_type = "application/wasm";
    if (url.ends_with(".svg")) content_type = "image/svg+xml"; // Add this
    if (url.ends_with(".woff2")) content_type = "font/woff2";  // Add this

    std::ostringstream response;
    response << "HTTP/1.1 200 OK\r\n"
             << "Content-Type: " << content_type << "\r\n"
             << "Content-Length: " << response_body.size() << "\r\n"
             << "Connection: close\r\n"
             << "Cross-Origin-Opener-Policy: same-origin\r\n"
             << "Cross-Origin-Embedder-Policy: require-corp\r\n\r\n"
             << response_body;

    boost::asio::write(socket, boost::asio::buffer(response.str()));
}

int main() {
    try {
        NetworkManager LocalNetworkServer;
        LocalNetworkServer.GetIOContext().run();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
