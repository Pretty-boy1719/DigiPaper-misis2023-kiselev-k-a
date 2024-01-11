#pragma once
#ifndef DIGIPAPER_DIGIPAPER_HPP_20240105 
#define DIGIPAPER_DIGIPAPER_HPP_20240105

#include <vector>
#include <iostream>
#include <numbers>
#include <fstream>
#include <cmath>
#include <iomanip>

#include <Eigen/Dense>
#include <Eigen/Geometry>


typedef long long ll;
const double cPi = std::numbers::pi_v<double>;


struct Space {

	struct Point3
	{
		double x;
		double y;
		double z;
		bool is_selected = false;

		~Point3() = default;

		Point3(double xx, double yy, double zz, bool select = false);
		Point3();
	};

	struct Line2 {
		double A;
		double B;
		double C;

		Line2();

		Line2(double a, double b, double c);
	};

	struct CylindricalCoordinate {
		double r;
		double phi;
		double z;

		CylindricalCoordinate();

		CylindricalCoordinate(double dist, double angle, double height);
	};

	std::vector<Point3> surface;
	const ll dim_;
	const ll cube_;

	~Space() = default;

	Space();

	Space(ll dimension);

	Point3 compute_midpoint(Point3 a1, Point3 a2);

	Line2 compute_perpendicular_line(Line2 line, Point3 mid);

	double compute_distance_to_line(Point3 m, Line2 line);

	Line2 compute_line_points(Point3 p1, Point3 p2);

	bool is_point_below_line(Point3 p, Line2 l);

	// Функция для вычисления угла между двумя прямыми
	double calculate_angle_between_lines(const Eigen::Vector2d& line1, const Eigen::Vector2d& line2);

	CylindricalCoordinate to_cylindr_coordinate(Point3 p, Line2 perp_line, double r, Line2 fold);

	Point3 cylindrical_to_cartesian(CylindricalCoordinate cylCoords, Point3 offset, double angle);

	Point3 round_cord(Point3 p);

	ll cord_to_vec(double xx, double yy, double zz);

	Point3 vec_to_cord(ll num);

	bool is_paper(ll x, ll y, ll z);

	void change_point(Point3 p, bool is_paper);

	Point3 get_point(ll x, ll y, ll z);

	void cylindrical_bending(Point3 a1, Point3 a2, double radius);

	std::ostream& WriteTo(std::ostream& ostrm);
};

#endif