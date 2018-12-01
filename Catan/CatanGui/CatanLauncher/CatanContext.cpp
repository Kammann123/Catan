#include "CatanContext.h"

CatanContext::
CatanContext() : game(), networking(game) {
	this->username = "";
	this->ip = "";
	this->port = 0;
}

void CatanContext::setUsername(string name)
{
	this->username = name;
}

void CatanContext::setIp(string ip)
{
	this->ip = ip;
}

void CatanContext::setPort(unsigned int port) {
	this->port = port;
}

string CatanContext::getUsername(void)
{
	return username;
}

string CatanContext::getIp(void)
{
	return ip;
}

unsigned int CatanContext::getPort(void)
{
	return port;
}

CatanGame& CatanContext::getGame(void)
{
	return game;
}

CatanNetworking& CatanContext::getNetworking(void)
{
	return networking;
}