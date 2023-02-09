#ifndef TIN_TORRENTLIKEP2P_UTILS_H
#define TIN_TORRENTLIKEP2P_UTILS_H

#include <string>
#include <netinet/in.h>

void errno_abort(const std::string &header);

std::pair<unsigned long, unsigned short> convertAddress(sockaddr_in address);
unsigned long convertAddressLong(sockaddr_in address);
std::string getMyAddress(int socket);
unsigned int getCountBytesToWrite(unsigned long long fileSize, unsigned long index, unsigned int chunkSize);

#endif //TIN_TORRENTLIKEP2P_UTILS_H
