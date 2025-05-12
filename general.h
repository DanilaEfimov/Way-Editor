#ifndef GENERAL_H
#define GENERAL_H

#define NAME "Way Editor"

#define WHITE_F ":/qss/white.css"
#define BLACK_F ":/qss/black.css"
#define ERROR_QSS_F ":/qss/error_box.css"
#define WARNING_QSS_F ":/qss/warning_box.css"
#define INPUT_FORM_QSS_F ":/qss/input_box.css"
#define ICON_F ":/icons/way_editor.ico"
#define NEW_FILE_F ":/icons/new_file.ico"
#define OPEN_F ":/icons/open.ico"
#define SAVE_F ":/icons/save.ico"
#define REMOVE_F ":/icons/remove.ico"
#define ERROR_ICO_F ":/icons/error.ico"
#define INPUT_FORM_F ":/icons/input_form.ico"
#define WARNING_ICO_F ":/icons/warning.ico"
#define MSG_F ":/texts/from_developers.txt"
#define HELP_F ":/texts/help.txt"

// ^^^ resource path / other VVV
#define ERROR_BOX "error_box"
#define WARNING_BOX "warning_box"
#define MAX_DIALOG_SIZE QSize(300,200);
#define ERROR_CODE -1
#define SUCCESS_CODE 0

#define _HELLO_ "From developers"
#define _ERROR_TITLE_ "Something went wrong"
#define _WARNING_TITLE_ " WARNING "
#define _FORM_TITLE_ "New Graph file"
#define _INPUT_PATH_MSG_ "Input file path: "
#define _INPUT_TYPE_MSG_ "Input graph's type: "
#define _ENTER_ "Enter"
#define _INDEFINED_COMMAND_ "UNDEFINED COMMAND\n"
#define _UNDEFINED_ERROR_ "Undefined error, please, try again."
#define _UNDFINED_FILE_TYPE "Undefined file type, Way Editor \
\n doesn't can to pars it."
#define _UNDEFINED_GRAPH_TYPE_ "Something went wrong. \
\n Way Editor doesn't can create new graph."
#define _INVALID_INPUT_ "Was inputed unparsable data, plese, check \
\n Your input."
#define _PATH_PARS_WARNING_ "Issues with path parsing. \
\n You can try rename file: in file name can be \
\n extra '.' ."
#define _EMPTY_INPUT_ "Empty input."
#define _GRAPH_TYPE_PARS_WARNING_ "Issues with graph's type pars. \
\n plese, check Your input or update Way Editor."
#define _INVALID_DIR_ERROR_ "No such file or directiry."
#define _PROHIBITED_CHARACTERS_ "Path contains prohibited chars."
#define _PROBLEM_OF_OPEN_FILE_ "Issues with opening file. \
\n You can try other path (can be problems with access rights). "
#define _OPEN_FILE_ERROR_ "Could not open file."

// ^^^ other / console answers vvv
#define _UNDEFINED_ARG_ERROR "Undefined argument."
#define _UNDEFINED_OP_ERROR_ "Undefined operation."
#define _GRAPH_TYPE_CMD_ERROR_ "The command is not supported by this type of graph."
#define _EXEC_ERROR_ "Command cannot be executed."

#include <map>
#include <string>

typedef std::pair<std::string, int> ext_key, type_key, op_key;
typedef std::pair<int, std::string> r_ext_key, r_type_key;
typedef std::pair<int, int> permutation;

enum fileTypes {
    MAT = 1, EL, VL
};

enum {
    ZERO,
    ONE, TWO, THREE, FOUR,
    LIMITLESS,
    EVEN, NOT_EVEN
};

enum operations {
    clear_text,
    add_vertex, add_edge, erase_vertex, erase_edge, degree,
    kosaraju,
};

enum graphTypes {
    udirgraph = 1, dirgraph, upseudograph, dpseudograph,
    uweightedgraph, dweightedgraph, tree, bitree, weightedtree
};

const std::map<std::string, int> extentions {
    ext_key(".mat", MAT), ext_key(".el", EL), ext_key(".vl", VL),
};

const std::map<int, std::string> r_extentions {
    r_ext_key(MAT, ".mat"), r_ext_key(EL, ".el"), r_ext_key(VL, ".vl"),
};

const std::map<std::string, int> graphs {   // ~500 bytes
    type_key("udirgraph", udirgraph), type_key("dirgraph", dirgraph), type_key("upseudograph", upseudograph),
    type_key("dpseudograph", dpseudograph), type_key("uweightedgraph", uweightedgraph), type_key("dweightedgraph", dweightedgraph),
    type_key("tree", tree), type_key("bitree", bitree), type_key("weightedtree", weightedtree),
};

const std::map<int, std::string> r_graphs {
    r_type_key(udirgraph, "udirgraph"), r_type_key(dirgraph, "dirgraph"), r_type_key(upseudograph, "upseudograph"),
    r_type_key(dpseudograph, "dpseudograph"), r_type_key(uweightedgraph, "uweightedgraph"), r_type_key(dweightedgraph, "dweightedgraph"),
    r_type_key(tree, "tree"), r_type_key(bitree, "bitree"), r_type_key(weightedtree, "weightedtree"),
};

const std::map<std::string, int> op_str{
    op_key("clear", clear_text), op_key("addV", add_vertex), op_key("addE", add_edge),
    op_key("eraseV", erase_vertex), op_key("eraseE", erase_edge), op_key("degree", degree),
    op_key("kosaraju",kosaraju),
};

const std::map<int, int> op_argc{
    permutation(clear_text, ONE), permutation(add_vertex, LIMITLESS), permutation(add_edge, TWO),
    permutation(erase_vertex, TWO), permutation(erase_edge, LIMITLESS), permutation(degree, ONE),
    permutation(kosaraju, ZERO),
};

const std::map<int, int> argc_op{
    permutation(ONE, clear_text), permutation(LIMITLESS, add_vertex), permutation(EVEN, add_edge),
    permutation(ONE, erase_vertex), permutation(EVEN, erase_edge), permutation(ONE, degree),
     permutation(ZERO, kosaraju),
};

#endif // GENERAL_H
