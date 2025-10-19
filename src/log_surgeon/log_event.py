class LogEvent:
    """ """

    def __init__(self) -> None:
        _log_message: str = ""
        _var_dict: dict[str, str | list[str | int | float]] = []

    def get_log_message(self) -> str:
        return _log_message

    def __getitem__(self, variable_name: str) -> str | list[str | int | float]:
        return _var_dict[variable_name]

    def __str__(self) -> str:
        return get_log_message()

    def __repr__(self) -> str:
        return get_log_message()
