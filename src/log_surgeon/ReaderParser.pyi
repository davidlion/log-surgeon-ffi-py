from typing import IO

from log_event import LogEvent

class ReaderParser:
    def __init__(self, input_stream: IO[bytes], schema: str): ...
    def next_log_event(self) -> LogEvent | None: ...
