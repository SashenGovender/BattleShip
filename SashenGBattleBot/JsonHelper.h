#ifndef JSONHELPER
#define JSONHELPER

#include "json/json.h"

class JsonHelper
{
private:
   Json::Value _jsonData;

   JsonHelper(Json::Value* jData);
   bool IsValidIndex(int key);

public:
   JsonHelper();
   bool Deserialise(const char *data);
   void Serialise(std::string& jsonStringBuffer);
   void Release();
   int GetInt(char* key);
   int GetInt(int key);
   double GetDouble(int key);
   double GetDouble(char* key);
   int GetCString(char* key, char* buffer, int bufferSize);
   int GetCString(int key, char* buffer, int bufferSize);
   std::string GetString(char* key);
   std::string GetString(int key);
   bool GetBool(int key);
   bool GetBool(char* key);
   JsonHelper* GetJsonObject(int key);
   JsonHelper* GetJsonObject(char *key);
   Json::Value* GetJsonMainObject();
   int GetArraySize(int key);
   int GetArraySize(char* key);
   JsonHelper* GetArray(int key);
   JsonHelper* GetArray(char* key);
   Json::Value GetArrayValue(int key, int index);
   void AddInt(int key, int value);
   void AddInt(char* key, int value);
   void AddDouble(int key, double value);
   void AddDouble(char* key, double value);
   void AddString(int key, char* value);
   void AddString(char* key, char* value);
   void AddBool(int key, bool value);
   void AddBool(char* key, bool value);
   void AddJsonObject(int key, JsonHelper* object);
   void AddJsonObject(char* key, JsonHelper* object);
};

#endif
