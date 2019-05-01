namespace color
{

#ifndef NO_COLOR_OUTPUT

const auto FG_BLACK = "\033[30m";
const auto BG_BLACK = "\033[40m";
const auto FG_RED = "\033[31m";
const auto BG_RED = "\033[41m";
const auto FG_GREEN = "\033[32m";
const auto BG_GREEN = "\033[42m";
const auto FG_YELLOW = "\033[33m";
const auto BG_YELLOW = "\033[43m";
const auto FG_BLUE = "\033[34m";
const auto BG_BLUE = "\033[44m";
const auto FG_MAGENTA = "\033[35m";
const auto BG_MAGENTA = "\033[45m";
const auto FG_CYAN = "\033[36m";
const auto BG_CYAN = "\033[46m";
const auto FG_WHITE = "\033[37m";
const auto BG_WHITE = "\033[47m";
const auto OP_RESET = "\033[0m";
const auto OP_BOLD = "\033[1m";
const auto OP_BOLD_OFF = "\033[21m";
const auto OP_UNDERLINE = "\033[4m";
const auto OP_UNDERLINE_OFF = "\033[24m";
const auto OP_INVERSE = "\033[7m";
const auto OP_INVERSE_OFF = "\033[27m";

#else

const auto FG_BLACK = "";
const auto BG_BLACK = "";
const auto FG_RED = "";
const auto BG_RED = "";
const auto FG_GREEN = "";
const auto BG_GREEN = "";
const auto FG_YELLOW = "";
const auto BG_YELLOW = "";
const auto FG_BLUE = "";
const auto BG_BLUE = "";
const auto FG_MAGENTA = "";
const auto BG_MAGENTA = "";
const auto FG_CYAN = "";
const auto BG_CYAN = "";
const auto FG_WHITE = "";
const auto BG_WHITE = "";
const auto OP_RESET = "";
const auto OP_BOLD = "";
const auto OP_BOLD_OFF = "";
const auto OP_UNDERLINE = "";
const auto OP_UNDERLINE_OFF = "";
const auto OP_INVERSE = "";
const auto OP_INVERSE_OFF = "";

#endif

} // namespace color