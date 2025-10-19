#include <wrapped_facade_headers/Python.hpp>

#include "PyLogEvent.hpp"

#include <cstddef>
#include <cstdint>
#include <log_surgeon_ffi/api_decoration.hpp>
#include <log_surgeon_ffi/LogEvent.hpp>
#include <log_surgeon_ffi/PyObjectCast.hpp>
#include <log_surgeon_ffi/PyObjectUtils.hpp>
#include <log_surgeon_ffi/utils.hpp>
#include <new>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>

namespace log_surgeon_ffi {
// namespace {
// /**
//  * Constant keys used to serialize/deserialize `PyLogEvent` objects through
//  * `__getstate__` and
//  * `__setstate__` methods.
//  */
// constexpr std::string_view cStateLogMessage{"log_message"};
// constexpr std::string_view cStateTimestamp{"timestamp"};
// constexpr std::string_view cStateFormattedTimestamp{"formatted_timestamp"};
// constexpr std::string_view cStateIndex{"index"};

// // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
// PyDoc_STRVAR(
//         cPyLogEventDoc,
//         "This class represents a deserialzied log event and provides ways to "
//         "access the underlying "
//         "log data, including the log message, the timestamp, and the log event "
//         "index. "
//         "Normally, this class will be instantiated by the FFI IR deserialization "
//         "methods.\n"
//         "However, with the `__init__` method provided below, direct instantiation "
//         "is also "
//         "possible.\n\n"
//         "The signature of `__init__` method is shown as following:\n\n"
//         "__init__(self, log_message, timestamp, index=0, metadata=None)\n\n"
//         "Initializes an object that represents a log event. Notice that each "
//         "object should be "
//         "strictly initialized only once. Double initialization will result in "
//         "memory leaks.\n\n"
//         ":param log_message: The message content of the log event.\n"
//         ":param timestamp: The timestamp of the log event.\n"
//         ":param index: The message index (relative to the source CLP IR stream) of "
//         "the log event.\n"
//         ":param metadata: The PyMetadata instance that represents the source CLP "
//         "IR stream. "
//         "It is set to None by default.\n"
// );
// LOG_SURGEON_FFI_METHOD auto PyLogEvent_init(PyLogEvent* self, PyObject* args, PyObject* keywords)
//         -> int;

// /**
//  * Callback of `PyLogEvent` deallocator.
//  * @param self
//  */
// LOG_SURGEON_FFI_METHOD auto PyLogEvent_dealloc(PyLogEvent* self) -> void;

// // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
// PyDoc_STRVAR(
//         cPyLogEventGetStateDoc,
//         "__getstate__(self)\n"
//         "--\n\n"
//         "Serializes the log event (should be called by the Python pickle "
//         "module).\n\n"
//         ":return: Serialized log event in a Python dictionary.\n"
// );
// LOG_SURGEON_FFI_METHOD auto PyLogEvent_getstate(PyLogEvent* self) -> PyObject*;

// // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
// PyDoc_STRVAR(
//         cPyLogEventSetStateDoc,
//         "__setstate__(self, state)\n"
//         "--\n\n"
//         "Deserializes the log event from a state dictionary.\n\n"
//         "Note: this function is exclusively designed for invocation by the Python "
//         "pickle module. "
//         "Assumes `self` is uninitialized and will allocate the underlying memory. "
//         "If"
//         "`self` is already initialized this will result in memory leaks.\n\n"
//         ":param state: Serialized log event represented by a Python dictionary. It "
//         "is anticipated "
//         "to be the valid output of the `__getstate__` method.\n"
//         ":return: None\n"
// );
// LOG_SURGEON_FFI_METHOD auto PyLogEvent_setstate(PyLogEvent* self, PyObject* state) -> PyObject*;

// /**
//  * Callback of `PyLogEvent`'s `__str__` method.
//  * @param self
//  * @return PyLogEvent::get_formatted_log_message
//  */
// LOG_SURGEON_FFI_METHOD auto PyLogEvent_str(PyLogEvent* self) -> PyObject*;

// /**
//  * Callback of `PyLogEvent`'s `__repr__` method.
//  * @param self
//  * @return Python string representation of PyLogEvent state.
//  */
// LOG_SURGEON_FFI_METHOD auto PyLogEvent_repr(PyLogEvent* self) -> PyObject*;

// // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
// PyDoc_STRVAR(
//         cPyLogEventGetLogMessageDoc,
//         "get_log_message(self)\n"
//         "--\n\n"
//         "Gets the log message of the log event.\n\n"
//         ":return: The log message.\n"
// );
// LOG_SURGEON_FFI_METHOD auto PyLogEvent_get_log_message(PyLogEvent* self) -> PyObject*;

// // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
// PyDoc_STRVAR(
//         cPyLogEventGetTimestampDoc,
//         "get_timestamp(self)\n"
//         "--\n\n"
//         "Gets the Unix epoch timestamp in milliseconds of the log event.\n\n"
//         ":return: The timestamp in milliseconds.\n"
// );
// LOG_SURGEON_FFI_METHOD auto PyLogEvent_get_timestamp(PyLogEvent* self) -> PyObject*;

// // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
// PyDoc_STRVAR(
//         cPyLogEventGetIndexDoc,
//         "get_index(self)\n"
//         "--\n\n"
//         "Gets the message index (relative to the source CLP IR stream) of "
//         "the log event. This "
//         "index is set to 0 by default.\n\n"
//         ":return: The log event index.\n"
// );
// LOG_SURGEON_FFI_METHOD auto PyLogEvent_get_index(PyLogEvent* self) -> PyObject*;

// // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
// PyDoc_STRVAR(
//         cPyLogEventMatchQueryDoc,
//         "match_query(self, query)\n"
//         "--\n\n"
//         "Matches the underlying log event against the given query. Refer to the "
//         "documentation of "
//         "log_surgeon_ffi.Query for more details.\n\n"
//         ":param query: Input Query object.\n"
//         ":return: True if the log event matches the query, False otherwise.\n"
// );
// LOG_SURGEON_FFI_METHOD auto PyLogEvent_match_query(PyLogEvent* self, PyObject* query) ->
// PyObject*;

// // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
// PyDoc_STRVAR(
//         cPyLogEventGetFormattedMessageDoc,
//         "get_formatted_message(self, timezone=None)\n"
//         "--\n\n"
//         "Gets the formatted log message of the log event.\n\n"
//         "If a specific timezone is provided, it will be used to format the "
//         "timestamp. "
//         "Otherwise, the timestamp will be formatted using the timezone from the "
//         "source CLP IR "
//         "stream.\n\n"
//         ":param timezone: Python tzinfo object that specifies a timezone.\n"
//         ":return: The formatted message.\n"
// );
// LOG_SURGEON_FFI_METHOD auto
// PyLogEvent_get_formatted_message(PyLogEvent* self, PyObject* args, PyObject* keywords) ->
// PyObject*;

// // NOLINTNEXTLINE(*-avoid-c-arrays,
// // cppcoreguidelines-avoid-non-const-global-variables)
// PyMethodDef PyLogEvent_method_table[]{
//         {"get_log_message",
//          py_c_function_cast(PyLogEvent_get_log_message),
//          METH_NOARGS,
//          static_cast<char const*>(cPyLogEventGetLogMessageDoc)},

//         {"get_timestamp",
//          py_c_function_cast(PyLogEvent_get_timestamp),
//          METH_NOARGS,
//          static_cast<char const*>(cPyLogEventGetTimestampDoc)},

//         {"get_index",
//          py_c_function_cast(PyLogEvent_get_index),
//          METH_NOARGS,
//          static_cast<char const*>(cPyLogEventGetIndexDoc)},

//         {"get_formatted_message",
//          py_c_function_cast(PyLogEvent_get_formatted_message),
//          METH_KEYWORDS | METH_VARARGS,
//          static_cast<char const*>(cPyLogEventGetFormattedMessageDoc)},

//         {"match_query",
//          py_c_function_cast(PyLogEvent_match_query),
//          METH_O,
//          static_cast<char const*>(cPyLogEventMatchQueryDoc)},

//         {"__getstate__",
//          py_c_function_cast(PyLogEvent_getstate),
//          METH_NOARGS,
//          static_cast<char const*>(cPyLogEventGetStateDoc)},

//         {"__setstate__",
//          py_c_function_cast(PyLogEvent_setstate),
//          METH_O,
//          static_cast<char const*>(cPyLogEventSetStateDoc)},

//         {nullptr}
// };

// // NOLINTBEGIN(cppcoreguidelines-pro-type-*-cast)
// // NOLINTNEXTLINE(*-avoid-c-arrays,
// // cppcoreguidelines-avoid-non-const-global-variables)
// PyType_Slot PyLogEvent_slots[]{
//         {Py_tp_alloc, reinterpret_cast<void*>(PyType_GenericAlloc)},
//         {Py_tp_dealloc, reinterpret_cast<void*>(PyLogEvent_dealloc)},
//         {Py_tp_new, reinterpret_cast<void*>(PyType_GenericNew)},
//         {Py_tp_init, reinterpret_cast<void*>(PyLogEvent_init)},
//         {Py_tp_str, reinterpret_cast<void*>(PyLogEvent_str)},
//         {Py_tp_repr, reinterpret_cast<void*>(PyLogEvent_repr)},
//         {Py_tp_methods, static_cast<void*>(PyLogEvent_method_table)},
//         {Py_tp_doc, const_cast<void*>(static_cast<void const*>(cPyLogEventDoc))},
//         {0, nullptr}
// };
// // NOLINTEND(cppcoreguidelines-pro-type-*-cast)

// /**
//  * PyLogEvent Python type specifications.
//  */
// // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
// PyType_Spec PyLogEvent_type_spec{
//         "log_surgeon_ffi.ir.native.LogEvent",
//         sizeof(PyLogEvent),
//         0,
//         Py_TPFLAGS_DEFAULT,
//         static_cast<PyType_Slot*>(PyLogEvent_slots)
// };

// LOG_SURGEON_FFI_METHOD auto PyLogEvent_init(PyLogEvent* self, PyObject* args, PyObject* keywords)
//         -> int {
//     static char keyword_message[]{"log_message"};
//     static char keyword_timestamp[]{"timestamp"};
//     static char keyword_message_idx[]{"index"};
//     static char keyword_metadata[]{"metadata"};
//     static char* keyword_table[]{
//             static_cast<char*>(keyword_message),
//             static_cast<char*>(keyword_timestamp),
//             static_cast<char*>(keyword_message_idx),
//             static_cast<char*>(keyword_metadata),
//             nullptr
//     };

//     // If the argument parsing fails, `self` will be deallocated. We must reset
//     // all pointers to nullptr in advance, otherwise the deallocator might trigger
//     // segmentation fault.
//     self->default_init();

//     char const* log_message{nullptr};
//     clp::ir::epoch_time_ms_t timestamp{0};
//     size_t index{0};
//     PyObject* metadata{Py_None};
//     if (false
//         == static_cast<bool>(PyArg_ParseTupleAndKeywords(
//                 args,
//                 keywords,
//                 "sL|KO",
//                 static_cast<char**>(keyword_table),
//                 &log_message,
//                 &timestamp,
//                 &index,
//                 &metadata
//         )))
//     {
//         return -1;
//     }

//     auto const has_metadata{Py_None != metadata};
//     if (has_metadata
//         && false == static_cast<bool>(PyObject_TypeCheck(metadata, PyMetadata::get_py_type())))
//     {
//         PyErr_SetString(
//                 PyExc_TypeError,
//                 get_c_str_from_constexpr_string_view(log_surgeon_ffi::cPyTypeError)
//         );
//         return -1;
//     }

//     if (false
//         == self->init(
//                 log_message,
//                 timestamp,
//                 index,
//                 has_metadata ? py_reinterpret_cast<PyMetadata>(metadata) : nullptr
//         ))
//     {
//         return -1;
//     }
//     return 0;
// }

// LOG_SURGEON_FFI_METHOD auto PyLogEvent_dealloc(PyLogEvent* self) -> void {
//     self->clean();
//     PyObject_Del(self);
// }

// LOG_SURGEON_FFI_METHOD auto PyLogEvent_getstate(PyLogEvent* self) -> PyObject* {
//     auto* log_event{self->get_log_event()};
//     if (false == log_event->has_formatted_timestamp()) {
//         PyObjectPtr<PyObject> const formatted_timestamp_object{
//                 log_surgeon_ffi::py_utils_get_formatted_timestamp(
//                         log_event->get_timestamp(),
//                         self->has_metadata() ? self->get_py_metadata()->get_py_timezone() :
//                         Py_None
//                 )
//         };
//         auto* formatted_timestamp_ptr{formatted_timestamp_object.get()};
//         if (nullptr == formatted_timestamp_ptr) {
//             return nullptr;
//         }
//         std::string formatted_timestamp;
//         if (false == log_surgeon_ffi::parse_py_string(formatted_timestamp_ptr,
//         formatted_timestamp))
//         {
//             return nullptr;
//         }
//         log_event->set_formatted_timestamp(formatted_timestamp);
//     }

//     return Py_BuildValue(
//             "{sssssLsK}",
//             get_c_str_from_constexpr_string_view(cStateLogMessage),
//             log_event->get_log_message().c_str(),
//             get_c_str_from_constexpr_string_view(cStateFormattedTimestamp),
//             log_event->get_formatted_timestamp().c_str(),
//             get_c_str_from_constexpr_string_view(cStateTimestamp),
//             log_event->get_timestamp(),
//             get_c_str_from_constexpr_string_view(cStateIndex),
//             log_event->get_index()
//     );
// }

// LOG_SURGEON_FFI_METHOD auto PyLogEvent_setstate(PyLogEvent* self, PyObject* state) -> PyObject* {
//     self->default_init();

//     if (false == static_cast<bool>(PyDict_CheckExact(state))) {
//         PyErr_SetString(
//                 PyExc_ValueError,
//                 get_c_str_from_constexpr_string_view(log_surgeon_ffi::cSetstateInputError)
//         );
//         return nullptr;
//     }

//     auto* log_message_obj{
//             PyDict_GetItemString(state, get_c_str_from_constexpr_string_view(cStateLogMessage))
//     };
//     if (nullptr == log_message_obj) {
//         PyErr_Format(
//                 PyExc_KeyError,
//                 get_c_str_from_constexpr_string_view(log_surgeon_ffi::cSetstateKeyErrorTemplate),
//                 cStateLogMessage
//         );
//         return nullptr;
//     }
//     std::string log_message;
//     if (false == log_surgeon_ffi::parse_py_string(log_message_obj, log_message)) {
//         return nullptr;
//     }

//     auto* formatted_timestamp_obj{PyDict_GetItemString(
//             state,
//             get_c_str_from_constexpr_string_view(cStateFormattedTimestamp)
//     )};
//     if (nullptr == formatted_timestamp_obj) {
//         PyErr_Format(
//                 PyExc_KeyError,
//                 get_c_str_from_constexpr_string_view(log_surgeon_ffi::cSetstateKeyErrorTemplate),
//                 cStateFormattedTimestamp
//         );
//         return nullptr;
//     }
//     std::string formatted_timestamp;
//     if (false == log_surgeon_ffi::parse_py_string(formatted_timestamp_obj, formatted_timestamp))
//     {
//         return nullptr;
//     }

//     auto* timestamp_obj{
//             PyDict_GetItemString(state, get_c_str_from_constexpr_string_view(cStateTimestamp))
//     };
//     if (nullptr == timestamp_obj) {
//         PyErr_Format(
//                 PyExc_KeyError,
//                 get_c_str_from_constexpr_string_view(log_surgeon_ffi::cSetstateKeyErrorTemplate),
//                 cStateTimestamp
//         );
//         return nullptr;
//     }
//     clp::ir::epoch_time_ms_t timestamp{0};
//     if (false == log_surgeon_ffi::parse_py_int<clp::ir::epoch_time_ms_t>(timestamp_obj,
//     timestamp))
//     {
//         return nullptr;
//     }

//     auto* index_obj{PyDict_GetItemString(state,
//     get_c_str_from_constexpr_string_view(cStateIndex))}; if (nullptr == index_obj) {
//         PyErr_Format(
//                 PyExc_KeyError,
//                 get_c_str_from_constexpr_string_view(log_surgeon_ffi::cSetstateKeyErrorTemplate),
//                 cStateIndex
//         );
//         return nullptr;
//     }
//     size_t index{0};
//     if (false == log_surgeon_ffi::parse_py_int<size_t>(index_obj, index)) {
//         return nullptr;
//     }

//     if (false == self->init(log_message, timestamp, index, nullptr, formatted_timestamp)) {
//         return nullptr;
//     }

//     Py_RETURN_NONE;
// }

// LOG_SURGEON_FFI_METHOD auto PyLogEvent_str(PyLogEvent* self) -> PyObject* {
//     return self->get_formatted_message();
// }

// LOG_SURGEON_FFI_METHOD auto PyLogEvent_repr(PyLogEvent* self) -> PyObject* {
//     return PyObject_Repr(PyLogEvent_getstate(self));
// }

// LOG_SURGEON_FFI_METHOD auto PyLogEvent_get_log_message(PyLogEvent* self) -> PyObject* {
//     return PyUnicode_FromString(self->get_log_event()->get_log_message().c_str());
// }

// LOG_SURGEON_FFI_METHOD auto PyLogEvent_get_timestamp(PyLogEvent* self) -> PyObject* {
//     return PyLong_FromLongLong(self->get_log_event()->get_timestamp());
// }

// LOG_SURGEON_FFI_METHOD auto PyLogEvent_get_index(PyLogEvent* self) -> PyObject* {
//     return PyLong_FromLongLong(static_cast<int64_t>(self->get_log_event()->get_index()));
// }

// LOG_SURGEON_FFI_METHOD auto PyLogEvent_match_query(PyLogEvent* self, PyObject* query) ->
// PyObject* {
//     if (false == static_cast<bool>(PyObject_TypeCheck(query, PyQuery::get_py_type()))) {
//         PyErr_SetString(PyExc_TypeError, get_c_str_from_constexpr_string_view(cPyTypeError));
//         return nullptr;
//     }
//     auto* py_query{py_reinterpret_cast<PyQuery>(query)};
//     return get_py_bool(py_query->get_query()->matches(*self->get_log_event()));
// }

// LOG_SURGEON_FFI_METHOD auto
// PyLogEvent_get_formatted_message(PyLogEvent* self, PyObject* args, PyObject* keywords)
//         -> PyObject* {
//     static char keyword_timezone[]{"timezone"};
//     static char* key_table[]{static_cast<char*>(keyword_timezone), nullptr};

//     PyObject* timezone{Py_None};
//     if (false
//         == static_cast<bool>(PyArg_ParseTupleAndKeywords(
//                 args,
//                 keywords,
//                 "|O",
//                 static_cast<char**>(key_table),
//                 &timezone
//         )))
//     {
//         return nullptr;
//     }

//     return self->get_formatted_message(timezone);
// }
// }  // namespace

// auto PyLogEvent::get_py_type() -> PyTypeObject* {
//     return m_py_type.get();
// }

// auto PyLogEvent::module_level_init(PyObject* py_module) -> bool {
//     static_assert(std::is_trivially_destructible<PyLogEvent>());
//     auto* type{py_reinterpret_cast<PyTypeObject>(PyType_FromSpec(&PyLogEvent_type_spec))};
//     m_py_type.reset(type);
//     if (nullptr == type) {
//         return false;
//     }
//     return add_python_type(get_py_type(), "LogEvent", py_module);
// }

// auto PyLogEvent::create_new_log_event(
//         std::string_view log_message,
//         clp::ir::epoch_time_ms_t timestamp,
//         size_t index,
//         PyMetadata* metadata
// ) -> PyLogEvent* {
//     // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
//     PyLogEvent* self{PyObject_New(PyLogEvent, get_py_type())};
//     if (nullptr == self) {
//         return nullptr;
//     }
//     self->default_init();
//     if (false == self->init(log_message, timestamp, index, metadata)) {
//         return nullptr;
//     }
//     return self;
// }

// auto PyLogEvent::init(
//         std::string_view log_message,
//         clp::ir::epoch_time_ms_t timestamp,
//         size_t index,
//         PyMetadata* metadata,
//         std::optional<std::string_view> formatted_timestamp
// ) -> bool {
//     // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
//     m_log_event = new (std::nothrow) LogEvent(log_message, timestamp, index,
//     formatted_timestamp); if (nullptr == m_log_event) {
//         PyErr_SetString(
//                 PyExc_RuntimeError,
//                 get_c_str_from_constexpr_string_view(log_surgeon_ffi::cOutOfMemoryError)
//         );
//         return false;
//     }
//     set_metadata(metadata);
//     return true;
// }

// auto PyLogEvent::get_formatted_message(PyObject* timezone) -> PyObject* {
//     auto cache_formatted_timestamp{false};
//     if (Py_None == timezone) {
//         if (m_log_event->has_formatted_timestamp()) {
//             // If the formatted timestamp exists, it constructs the raw message
//             // without calling python level format function
//             return PyUnicode_FromFormat(
//                     "%s%s",
//                     m_log_event->get_formatted_timestamp().c_str(),
//                     m_log_event->get_log_message().c_str()
//             );
//         }
//         if (has_metadata()) {
//             timezone = m_py_metadata->get_py_timezone();
//             cache_formatted_timestamp = true;
//         }
//     }

//     PyObjectPtr<PyObject> const formatted_timestamp_object{
//             py_utils_get_formatted_timestamp(m_log_event->get_timestamp(), timezone)
//     };
//     auto* formatted_timestamp_ptr{formatted_timestamp_object.get()};
//     if (nullptr == formatted_timestamp_ptr) {
//         return nullptr;
//     }
//     std::string formatted_timestamp;
//     if (false == parse_py_string(formatted_timestamp_ptr, formatted_timestamp)) {
//         return nullptr;
//     }

//     if (cache_formatted_timestamp) {
//         m_log_event->set_formatted_timestamp(formatted_timestamp);
//     }
//     return PyUnicode_FromFormat(
//             "%s%s",
//             formatted_timestamp.c_str(),
//             m_log_event->get_log_message().c_str()
//     );
// }
}  // namespace log_surgeon_ffi
