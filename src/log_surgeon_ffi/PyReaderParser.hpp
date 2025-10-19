#ifndef LOG_SURGEON_FFI_PYREADERPARSER_HPP
#define LOG_SURGEON_FFI_PYREADERPARSER_HPP

#include <wrapped_facade_headers/Python.hpp>

#include <cstdint>
#include <log_surgeon/Constants.hpp>
#include <log_surgeon/ReaderParser.hpp>
#include <log_surgeon_ffi/PyObjectUtils.hpp>
#include <memory>

namespace log_surgeon_ffi {
/**
 * A PyObject structure for deserializing CLP key-value pair IR stream. The
 * underlying deserializer is pointed by `m_deserializer`, which reads the IR
 * stream from a Python `IO[byte]` object via `DeserializerBufferReader`.
 */
class PyReaderParser {
public:
    /**
     * Gets the `PyTypeObject` that represents `PyReaderParser`'s Python type.
     * This type is dynamically created and initialized during the execution of
     * `PyReaderParser::module_level_init`.
     * @return Python type object associated with `PyReaderParser`.
     */
    [[nodiscard]] static auto get_py_type() -> PyTypeObject* { return m_py_type.get(); }

    /**
     * Creates and initializes `PyReaderParser` as a Python type, and then
     * incorporates this type as a Python object into the py_module module.
     * @param py_module This is the Python module where the initialized
     * `PyReaderParser` will be incorporated.
     * @return true on success.
     * @return false on failure with the relevant Python exception and error set.
     */
    [[nodiscard]] static auto module_level_init(PyObject* py_module) -> bool;

    // Delete default constructor to disable direct instantiation.
    PyReaderParser() = delete;

    // Delete copy & move constructors and assignment operators
    PyReaderParser(PyReaderParser const&) = delete;
    PyReaderParser(PyReaderParser&&) = delete;
    auto operator=(PyReaderParser const&) -> PyReaderParser& = delete;
    auto operator=(PyReaderParser&&) -> PyReaderParser& = delete;

    // Destructor
    ~PyReaderParser() = default;

    /**
     * Deallocate/release all memory for Python dealloc.
     */
    auto dealloc() -> void;

    /**
     * Since the memory allocation of `PyReaderParser` is handled by CPython's
     * allocator, cpp constructors will not be explicitly called. This function
     * serves as the default constructor to initialize the underlying deserializer
     * and deserializer buffer reader. Other data members are assumed to be
     * zero-initialized by `default-init` method. It has to be manually called
     * whenever creating a new `PyReaderParser` object through CPython APIs.
     * @param input_stream The input IR stream. Must be a Python `IO[byte]`
     * object.
     * @param buffer_capacity The buffer capacity used to initialize the
     * underlying `PyReaderParserBufferReader`.
     * @param allow_incomplete_stream Whether to treat an incomplete CLP IR stream
     * as an error. When set to `true`, an incomplete stream is interpreted as the
     * end of the stream without raising an exception.
     * @return true on success.
     * @return false on failure with the relevant Python exception and error set.
     */
    [[nodiscard]] auto init(PyObject* input_stream, char const* schema_content) -> bool;

    /**
     * Deserializes the next key value pair log event from the IR stream.
     * @return A new reference to a `KeyValuePairLogEvent` object representing the
     * deserialized log event on success.
     * @return A new reference to `Py_None` when the end of IR stream is reached.
     * @return nullptr on failure with the relevant Python exception and error
     * set.
     */
    [[nodiscard]] auto done() -> bool;

    /**
     * Deserializes the next key value pair log event from the IR stream.
     * @return A new reference to a `KeyValuePairLogEvent` object representing the
     * deserialized log event on success.
     * @return A new reference to `Py_None` when the end of IR stream is reached.
     * @return nullptr on failure with the relevant Python exception and error
     * set.
     */
    [[nodiscard]] auto parse_next_log_event() -> PyObject*;

    /**
     * @return A pointer to the user-defined stream-level metadata, deserialized
     * from the stream's preamble, if defined.
     * @return std::nullptr if the user-defined stream-level metadata is not
     * defined.
     */
    // [[nodiscard]] auto get_user_defined_metadata() const -> nlohmann::json const*;

private:
    static inline PyObjectStaticPtr<PyTypeObject> m_py_type{nullptr};

    /**
     * Implements `IrUnitHandler::EndOfStreamHandle`.
     * This handle function sets the underlying `m_end_of_stream_reached` to true.
     * @return IRErrorCode::IRErrorCode_Success on success.
     */
    // [[maybe_unused]] auto handle_end_of_stream() -> clp::ffi::ir_stream::IRErrorCode {
    //     m_end_of_stream_reached = true;
    //     return clp::ffi::ir_stream::IRErrorCode::IRErrorCode_Success;
    // }

    /**
     * Implements `IrUnitHandler::LogEventHandle`.
     * This handle function sets the underlying `m_deserialized_log_event` with
     * the given input.
     * @param kv_log_event
     * @return IRErrorCode::IRErrorCode_Success on success.
     *
     */
    // [[nodiscard]] auto handle_log_event(clp::ffi::KeyValuePairLogEvent&& log_event)
    //         -> clp::ffi::ir_stream::IRErrorCode;

    PyObject_HEAD;
    PyObject* m_py_input_stream{nullptr};
    std::unique_ptr<log_surgeon::ReaderParser> m_parser;
};
}  // namespace log_surgeon_ffi

#endif  // LOG_SURGEON_FFI_PYREADERPARSER_HPP
