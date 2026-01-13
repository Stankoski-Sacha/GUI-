module;

#include <vector>

export module component;
/*
 * This file is used to define a struct that will hold every component that
 * window will have. Using a std::vector, from the code that the user write,
 * every elements will be initialized then moved inside the vector and then the
 * window takes the vector to have all component then they will be placed inside
 * the window
 */
export namespace GUI_COMP {
struct Component {};
} // namespace GUI_COMP
