#include "shape_path.hpp"
#include <math.h>
#include <iostream>
#include <sstream>
#include <string.h>

ShapePath::ShapePath(std::string command)
{
  //this->command = command;
  this->ParseCommandString(command);
  this->width = 200;
  this->height = 200;
}

cairo_surface_t* ShapePath::Render(double scale)
{
  cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                                        this->width * scale,
                                                        this->height * scale);
  cairo_t* cairo = cairo_create(surface);
  cairo_scale(cairo, scale, scale);

  if (this->debug) {
    // Draw a bounding box
    cairo_set_source_rgba(cairo, 1.0, 0, 0.9, 0.5);
    cairo_rectangle(cairo, 0, 0, this->width * scale, this->height * scale);
    cairo_stroke(cairo);
    // Draw center point
    cairo_set_source_rgba(cairo, 1.0, 0, 0.9, 0.8);
    cairo_arc(cairo, this->centerX, this->centerY, 2, 0, M_PI * 2); 
    cairo_fill(cairo);
  }

  cairo_move_to(cairo, this->centerX, this->centerY);
  cairo_set_source_rgb(cairo, 0, 0, 0);
  for (auto command : this->commands) {
    switch (std::get<0>(command)) {
    case ShapePath::Command::MOVE:
      cairo_move_to(cairo, std::get<1>(command), std::get<2>(command)); 
      break;
    case ShapePath::Command::LINE:
      cairo_line_to(cairo, std::get<1>(command), std::get<2>(command)); 
      break;
    case ShapePath::Command::MOVE_RELATIVE:
      cairo_rel_move_to(cairo, std::get<1>(command), std::get<2>(command)); 
      break;
    case ShapePath::Command::LINE_RELATIVE:
      cairo_rel_line_to(cairo, std::get<1>(command), std::get<2>(command)); 
      break;
    case ShapePath::Command::STROKE:
      cairo_stroke(cairo); 
      break;
    case ShapePath::Command::FILL:
      cairo_fill(cairo); 
      break;
    }
  }

  cairo_destroy(cairo);
  return surface;
}

void ShapePath::SetCommand(std::string commandString)
{
  // TODO: Validate commandString.
  this->ParseCommandString(commandString);
}

void ShapePath::ParseCommandString(std::string commandString)
{
  if (commandString.size() > 0) {
    std::vector<std::string> tokens;

    // Tokenize the command string and push into the array. Plus one for null-termination.
    char* command = (char*)malloc(commandString.size() + 1);
    strcpy(command, commandString.c_str());
    char* token = strtok(command, " ,");
    while (token != NULL) {
      tokens.push_back(std::string(token));
      token = strtok(NULL, " ,");
    }
    free(command);

    // Convert tokens to tuples that represent drawing instructions.
    // TODO: roughly redundant.
    this->commands.clear();
    for (int i = 0; i < tokens.size(); ++i) {
      std::string token = tokens[i];
      if (token == "M" || token == "MR") {
	double x;
	double y;
	ShapePath::Command instruction = token == "M" ? ShapePath::Command::MOVE : ShapePath::Command::MOVE_RELATIVE;
	std::istringstream(tokens[i+1]) >> x;
	std::istringstream(tokens[i+2]) >> y;
	this->commands.push_back(std::make_tuple(instruction, x, y, 0, 0, 0));
	i += 2;
      }
      if (token == "L" || token =="LR") {
	double x;
	double y;
	ShapePath::Command instruction = token == "L" ? ShapePath::Command::LINE : ShapePath::Command::LINE_RELATIVE;
	std::istringstream(tokens[i+1]) >> x;
	std::istringstream(tokens[i+2]) >> y;
	this->commands.push_back(std::make_tuple(instruction, x, y, 0, 0, 0));
	i += 2;
      }
      if (token == "S") {
	this->commands.push_back(std::make_tuple(ShapePath::Command::STROKE, 0, 0, 0, 0, 0));
      }
      if (token == "F") {
	this->commands.push_back(std::make_tuple(ShapePath::Command::FILL, 0, 0, 0, 0, 0));
      }
    }
  }
}
