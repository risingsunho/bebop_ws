// Generated by gencpp from file bebop_controller/AddTwoInts.msg
// DO NOT EDIT!


#ifndef BEBOP_CONTROLLER_MESSAGE_ADDTWOINTS_H
#define BEBOP_CONTROLLER_MESSAGE_ADDTWOINTS_H

#include <ros/service_traits.h>


#include <bebop_controller/AddTwoIntsRequest.h>
#include <bebop_controller/AddTwoIntsResponse.h>


namespace bebop_controller
{

struct AddTwoInts
{

typedef AddTwoIntsRequest Request;
typedef AddTwoIntsResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct AddTwoInts
} // namespace bebop_controller


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::bebop_controller::AddTwoInts > {
  static const char* value()
  {
    return "6a2e34150c00229791cc89ff309fff21";
  }

  static const char* value(const ::bebop_controller::AddTwoInts&) { return value(); }
};

template<>
struct DataType< ::bebop_controller::AddTwoInts > {
  static const char* value()
  {
    return "bebop_controller/AddTwoInts";
  }

  static const char* value(const ::bebop_controller::AddTwoInts&) { return value(); }
};


// service_traits::MD5Sum< ::bebop_controller::AddTwoIntsRequest> should match 
// service_traits::MD5Sum< ::bebop_controller::AddTwoInts > 
template<>
struct MD5Sum< ::bebop_controller::AddTwoIntsRequest>
{
  static const char* value()
  {
    return MD5Sum< ::bebop_controller::AddTwoInts >::value();
  }
  static const char* value(const ::bebop_controller::AddTwoIntsRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::bebop_controller::AddTwoIntsRequest> should match 
// service_traits::DataType< ::bebop_controller::AddTwoInts > 
template<>
struct DataType< ::bebop_controller::AddTwoIntsRequest>
{
  static const char* value()
  {
    return DataType< ::bebop_controller::AddTwoInts >::value();
  }
  static const char* value(const ::bebop_controller::AddTwoIntsRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::bebop_controller::AddTwoIntsResponse> should match 
// service_traits::MD5Sum< ::bebop_controller::AddTwoInts > 
template<>
struct MD5Sum< ::bebop_controller::AddTwoIntsResponse>
{
  static const char* value()
  {
    return MD5Sum< ::bebop_controller::AddTwoInts >::value();
  }
  static const char* value(const ::bebop_controller::AddTwoIntsResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::bebop_controller::AddTwoIntsResponse> should match 
// service_traits::DataType< ::bebop_controller::AddTwoInts > 
template<>
struct DataType< ::bebop_controller::AddTwoIntsResponse>
{
  static const char* value()
  {
    return DataType< ::bebop_controller::AddTwoInts >::value();
  }
  static const char* value(const ::bebop_controller::AddTwoIntsResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // BEBOP_CONTROLLER_MESSAGE_ADDTWOINTS_H