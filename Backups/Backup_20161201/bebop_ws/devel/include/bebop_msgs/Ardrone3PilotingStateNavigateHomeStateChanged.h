// Generated by gencpp from file bebop_msgs/Ardrone3PilotingStateNavigateHomeStateChanged.msg
// DO NOT EDIT!


#ifndef BEBOP_MSGS_MESSAGE_ARDRONE3PILOTINGSTATENAVIGATEHOMESTATECHANGED_H
#define BEBOP_MSGS_MESSAGE_ARDRONE3PILOTINGSTATENAVIGATEHOMESTATECHANGED_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace bebop_msgs
{
template <class ContainerAllocator>
struct Ardrone3PilotingStateNavigateHomeStateChanged_
{
  typedef Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> Type;

  Ardrone3PilotingStateNavigateHomeStateChanged_()
    : header()
    , state(0)
    , reason(0)  {
    }
  Ardrone3PilotingStateNavigateHomeStateChanged_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , state(0)
    , reason(0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint8_t _state_type;
  _state_type state;

   typedef uint8_t _reason_type;
  _reason_type reason;


    enum { state_available = 0u };
     enum { state_inProgress = 1u };
     enum { state_unavailable = 2u };
     enum { state_pending = 3u };
     enum { reason_userRequest = 0u };
     enum { reason_connectionLost = 1u };
     enum { reason_lowBattery = 2u };
     enum { reason_finished = 3u };
     enum { reason_stopped = 4u };
     enum { reason_disabled = 5u };
     enum { reason_enabled = 6u };
 

  typedef boost::shared_ptr< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> const> ConstPtr;

}; // struct Ardrone3PilotingStateNavigateHomeStateChanged_

typedef ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<std::allocator<void> > Ardrone3PilotingStateNavigateHomeStateChanged;

typedef boost::shared_ptr< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged > Ardrone3PilotingStateNavigateHomeStateChangedPtr;
typedef boost::shared_ptr< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged const> Ardrone3PilotingStateNavigateHomeStateChangedConstPtr;

// constants requiring out of line definition

   

   

   

   

   

   

   

   

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace bebop_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'bebop_msgs': ['/home/sunho/bebop_ws/src/bebop_autonomy/bebop_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> >
{
  static const char* value()
  {
    return "a0ed1aa9e290b08479307e09890d8141";
  }

  static const char* value(const ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xa0ed1aa9e290b084ULL;
  static const uint64_t static_value2 = 0x79307e09890d8141ULL;
};

template<class ContainerAllocator>
struct DataType< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bebop_msgs/Ardrone3PilotingStateNavigateHomeStateChanged";
  }

  static const char* value(const ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Ardrone3PilotingStateNavigateHomeStateChanged\n\
# auto-generated from up stream XML files at\n\
#   github.com/Parrot-Developers/libARCommands/tree/master/Xml\n\
# To check upstream commit hash, refer to last_build_info file\n\
# Do not modify this file by hand. Check scripts/meta folder for generator files.\n\
#\n\
# SDK Comment: Return home state.\\n Availability is related to gps fix, magnetometer calibration.\n\
\n\
Header header\n\
\n\
# State of navigate home\n\
uint8 state_available=0  # Navigate home is available\n\
uint8 state_inProgress=1  # Navigate home is in progress\n\
uint8 state_unavailable=2  # Navigate home is not available\n\
uint8 state_pending=3  # Navigate home has been received, but its process is pending\n\
uint8 state\n\
# Reason of the state\n\
uint8 reason_userRequest=0  # User requested a navigate home (available-&gt;inProgress)\n\
uint8 reason_connectionLost=1  # Connection between controller and product lost (available-&gt;inProgress)\n\
uint8 reason_lowBattery=2  # Low battery occurred (available-&gt;inProgress)\n\
uint8 reason_finished=3  # Navigate home is finished (inProgress-&gt;available)\n\
uint8 reason_stopped=4  # Navigate home has been stopped (inProgress-&gt;available)\n\
uint8 reason_disabled=5  # Navigate home disabled by product (inProgress-&gt;unavailable or available-&gt;unavailable)\n\
uint8 reason_enabled=6  # Navigate home enabled by product (unavailable-&gt;available)\n\
uint8 reason\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.state);
      stream.next(m.reason);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Ardrone3PilotingStateNavigateHomeStateChanged_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::bebop_msgs::Ardrone3PilotingStateNavigateHomeStateChanged_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "state: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.state);
    s << indent << "reason: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.reason);
  }
};

} // namespace message_operations
} // namespace ros

#endif // BEBOP_MSGS_MESSAGE_ARDRONE3PILOTINGSTATENAVIGATEHOMESTATECHANGED_H
