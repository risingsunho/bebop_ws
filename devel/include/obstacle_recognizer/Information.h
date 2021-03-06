// Generated by gencpp from file obstacle_recognizer/Information.msg
// DO NOT EDIT!


#ifndef OBSTACLE_RECOGNIZER_MESSAGE_INFORMATION_H
#define OBSTACLE_RECOGNIZER_MESSAGE_INFORMATION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace obstacle_recognizer
{
template <class ContainerAllocator>
struct Information_
{
  typedef Information_<ContainerAllocator> Type;

  Information_()
    : latitude(0.0)
    , longitude(0.0)
    , x(0.0)
    , y(0.0)
    , radius(0.0)
    , yaw(0.0)
    , velocity(0.0)
    , velocity_x(0.0)
    , velocity_y(0.0)  {
    }
  Information_(const ContainerAllocator& _alloc)
    : latitude(0.0)
    , longitude(0.0)
    , x(0.0)
    , y(0.0)
    , radius(0.0)
    , yaw(0.0)
    , velocity(0.0)
    , velocity_x(0.0)
    , velocity_y(0.0)  {
  (void)_alloc;
    }



   typedef double _latitude_type;
  _latitude_type latitude;

   typedef double _longitude_type;
  _longitude_type longitude;

   typedef double _x_type;
  _x_type x;

   typedef double _y_type;
  _y_type y;

   typedef double _radius_type;
  _radius_type radius;

   typedef double _yaw_type;
  _yaw_type yaw;

   typedef double _velocity_type;
  _velocity_type velocity;

   typedef double _velocity_x_type;
  _velocity_x_type velocity_x;

   typedef double _velocity_y_type;
  _velocity_y_type velocity_y;




  typedef boost::shared_ptr< ::obstacle_recognizer::Information_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::obstacle_recognizer::Information_<ContainerAllocator> const> ConstPtr;

}; // struct Information_

typedef ::obstacle_recognizer::Information_<std::allocator<void> > Information;

typedef boost::shared_ptr< ::obstacle_recognizer::Information > InformationPtr;
typedef boost::shared_ptr< ::obstacle_recognizer::Information const> InformationConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::obstacle_recognizer::Information_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::obstacle_recognizer::Information_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace obstacle_recognizer

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'obstacle_recognizer': ['/home/sunho/bebop_ws/src/obstacle_recognizer/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::obstacle_recognizer::Information_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::obstacle_recognizer::Information_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::obstacle_recognizer::Information_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::obstacle_recognizer::Information_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::obstacle_recognizer::Information_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::obstacle_recognizer::Information_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::obstacle_recognizer::Information_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e0cabc38676e4b76862576a407bfef61";
  }

  static const char* value(const ::obstacle_recognizer::Information_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe0cabc38676e4b76ULL;
  static const uint64_t static_value2 = 0x862576a407bfef61ULL;
};

template<class ContainerAllocator>
struct DataType< ::obstacle_recognizer::Information_<ContainerAllocator> >
{
  static const char* value()
  {
    return "obstacle_recognizer/Information";
  }

  static const char* value(const ::obstacle_recognizer::Information_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::obstacle_recognizer::Information_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 latitude\n\
float64 longitude\n\
float64 x\n\
float64 y\n\
float64 radius\n\
float64 yaw\n\
float64 velocity\n\
float64 velocity_x\n\
float64 velocity_y\n\
";
  }

  static const char* value(const ::obstacle_recognizer::Information_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::obstacle_recognizer::Information_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.latitude);
      stream.next(m.longitude);
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.radius);
      stream.next(m.yaw);
      stream.next(m.velocity);
      stream.next(m.velocity_x);
      stream.next(m.velocity_y);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Information_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::obstacle_recognizer::Information_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::obstacle_recognizer::Information_<ContainerAllocator>& v)
  {
    s << indent << "latitude: ";
    Printer<double>::stream(s, indent + "  ", v.latitude);
    s << indent << "longitude: ";
    Printer<double>::stream(s, indent + "  ", v.longitude);
    s << indent << "x: ";
    Printer<double>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<double>::stream(s, indent + "  ", v.y);
    s << indent << "radius: ";
    Printer<double>::stream(s, indent + "  ", v.radius);
    s << indent << "yaw: ";
    Printer<double>::stream(s, indent + "  ", v.yaw);
    s << indent << "velocity: ";
    Printer<double>::stream(s, indent + "  ", v.velocity);
    s << indent << "velocity_x: ";
    Printer<double>::stream(s, indent + "  ", v.velocity_x);
    s << indent << "velocity_y: ";
    Printer<double>::stream(s, indent + "  ", v.velocity_y);
  }
};

} // namespace message_operations
} // namespace ros

#endif // OBSTACLE_RECOGNIZER_MESSAGE_INFORMATION_H
