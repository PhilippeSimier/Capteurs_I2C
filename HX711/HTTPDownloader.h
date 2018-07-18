#ifndef HTTPDOWNLOADER_H
#define HTTPDOWNLOADER_H

#include <string>
/**
 * A non-threadsafe simple libcURL-easy based HTTP downloader
 */
class HTTPDownloader {

    public:
    HTTPDownloader();
    ~HTTPDownloader();

   /**
     * Download a file using HTTP GET and store in in a std::string
     * @param url The URL to download
     * @return The download result
     */
    std::string obtenirUrl(const std::string& url);

   private:
    void* curl;
};

#endif  /* HTTPDOWNLOADER_H */
