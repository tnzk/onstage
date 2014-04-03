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
  this->fillColor = std::make_tuple(1.0, 0, 0);
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
    case ShapePath::Command::ARC:
      cairo_arc(cairo, std::get<1>(command), std::get<2>(command), std::get<3>(command), std::get<4>(command), std::get<5>(command));
      break;
    case ShapePath::Command::CURVE:
      cairo_curve_to(cairo, std::get<1>(command), std::get<2>(command), std::get<3>(command), std::get<4>(command),
		            std::get<5>(command), std::get<6>(command));
      break;
    case ShapePath::Command::CURVE_RELATIVE:
      cairo_rel_curve_to(cairo, std::get<1>(command), std::get<2>(command), std::get<3>(command), std::get<4>(command),
		                std::get<5>(command), std::get<6>(command));
      break;
    case ShapePath::Command::STROKE:
      {
	double r = std::get<0>(this->strokeColor);
	double g = std::get<1>(this->strokeColor);
	double b = std::get<2>(this->strokeColor);
	cairo_set_source_rgb(cairo, r, g, b);
	cairo_set_line_width(cairo, 1.0);
	cairo_stroke_preserve(cairo); 
      }
      break;
    case ShapePath::Command::FILL:
      {
	double r = std::get<0>(this->fillColor);
	double g = std::get<1>(this->fillColor);
	double b = std::get<2>(this->fillColor);
	cairo_set_source_rgb(cairo, r, g, b);
	cairo_fill_preserve(cairo);
      }
      break;
    case ShapePath::Command::CLOSE:
      cairo_close_path(cairo); 
      break;
    }
  }

  cairo_destroy(cairo);
  return surface;
}

void ShapePath::SetFillColor(double r, double g, double b)
{
  this->fillColor = std::make_tuple(r, g, b);  
}

void ShapePath::SetStrokeColor(double r, double g, double b)
{
  this->strokeColor = std::make_tuple(r, g, b);  
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
	this->commands.push_back(std::make_tuple(instruction, x, y, 0, 0, 0, 0));
	i += 2;
      }
      if (token == "L" || token =="LR") {
	double x;
	double y;
	ShapePath::Command instruction = token == "L" ? ShapePath::Command::LINE : ShapePath::Command::LINE_RELATIVE;
	std::istringstream(tokens[i+1]) >> x;
	std::istringstream(tokens[i+2]) >> y;
	this->commands.push_back(std::make_tuple(instruction, x, y, 0, 0, 0, 0));
	i += 2;
      }
      if (token == "ARC" || token =="ARCN") {
	double xc;
	double yc;
	double radius;
	double angleBegins;
	double angleEnds;
	ShapePath::Command instruction = token == "ARC" ? ShapePath::Command::ARC : ShapePath::Command::ARC_NEGATIVE;
	std::istringstream(tokens[i+1]) >> xc;
	std::istringstream(tokens[i+2]) >> yc;
	std::istringstream(tokens[i+3]) >> radius;
	std::istringstream(tokens[i+4]) >> angleBegins;
	std::istringstream(tokens[i+5]) >> angleEnds;
	this->commands.push_back(std::make_tuple(instruction, xc, yc, radius, angleBegins, angleEnds, 0));
	i += 5;
      }
      if (token == "CURVE" || token =="CURVER") {
	double c1x;
	double c1y;
	double c2x;
	double c2y;
	double px;
	double py;
	ShapePath::Command instruction = token == "CURVE" ? ShapePath::Command::CURVE : ShapePath::Command::CURVE_RELATIVE;
	std::istringstream(tokens[i+1]) >> c1x;
	std::istringstream(tokens[i+2]) >> c1y;
	std::istringstream(tokens[i+3]) >> c2x;
	std::istringstream(tokens[i+4]) >> c2y;
	std::istringstream(tokens[i+5]) >> px;
	std::istringstream(tokens[i+6]) >> py;
	this->commands.push_back(std::make_tuple(instruction, c1x, c1y, c2x, c2y, px, py));
	i += 6;
      }
      if (token == "S") {
	this->commands.push_back(std::make_tuple(ShapePath::Command::STROKE, 0, 0, 0, 0, 0, 0));
      }
      if (token == "F") {
	this->commands.push_back(std::make_tuple(ShapePath::Command::FILL, 0, 0, 0, 0, 0, 0));
      }
      if (token == "Z") {
	this->commands.push_back(std::make_tuple(ShapePath::Command::CLOSE, 0, 0, 0, 0, 0, 0));
      }
    }
  }
}
