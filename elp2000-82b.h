/*
 * elp2000.h - ELP2000-82B main file.
 * Created by Serhii Tsyba (sertsy@gmail.com) on 21.04.10.
 *
 * This is an implementation of the semi-analytic lunar theory ELP 2000 version
 * 82B. It allows computation of a geocentric geometric lunar position and
 * hence allowing to compute lunar ephemeris.
 *
 * Four functions are given to compute geocentric moon position:
 *      a) geocentric_moon_position - computes position of the Moon in
 *         spherical coordinate system referred to the ELP 2000 reference
 *         frame, i.e. mean dynmical ecliptic of date and Brown's Departure
 *         Point γ'(2000) [1, p. 54].
 *      b) geocentric_moon_position_rect - computes position of the Moon in
 *         in three dimensional cartesian coordinate system referred to the
 *         ELP 2000 reference frame by converting the output of the function
 *         a) with formulas [3, p. 10].
 *      c) geocentric_moon_position_of_J2000 - computes position of the Moon
 *         in three dimensional rectangular coordiante system referred to
 *         the internal mean ecliptic and equinox of J2000 by converting the
 *         output of the function b) with formulas [3, p. 11].
 *      d) geocentric_moon_position_FK5 - computes position of the Moon in
 *         three dimensional cartesian coordiante system referred to the
 *         FK5 equator γFK5, i.e. mean equator and rotational mean equinox
 *         of J2000, by converting the output of the function c) with
 *         formulas [3, p. 11].
 *
 * Each of these functions takes a single input argument t - a time instant
 * measured in Julian centuries since the beginning of the epoch J2000 and
 * can be found by the following formula:
 *
 *              t = (JD - 2451545.0) / 36525
 *
 * where
 *      JD          is the Julian day number of the time instant when Moon's
 *                  position is to be computed;
 *      2451545.0   is the Julian day number of the beginning of the epoch
 *                  J2000;
 *      36525       is the amount of days in one Julian century;
 *
 * For dates greater than 1.5 January 2000 t is positive, for earlier dates t
 * is negative.
 *
 * Output units for spherical coordinates are arcseconds for longitude and
 * latitude and kilometers for distance. All rectangular coordinates are
 * measured in kilometers.
 *
 * The accuray of the theory ELP version ELP 2000-82B is different from
 * numerical ephemeris LE 51 of the NASA Jet Propulsion Laboratory in
 *      longitude - ±800 arcseconds
 *      latitude  - ±100 arcseconds
 *      distance  - ±0.1 kilometers
 * for the timeframe 1900 - 2000 A.D. and increases with time [1, p. 59, fig. 4].
 *
 * For more information on solution ELP version ELP 2000-82B refer to the
 * following papers:
 *      1) M. Chapront-Touzé and J. Chapront. The lunar ephemeris ELP 2000.
 *         Astronomy and Astrophysics, vol. 124, 1983, pp. 50-62.
 *      2) M. Chapront-Touzé and J. Chapront. ELP 2000-85: a semi-analytical
 *         lunar ephemeris adequate for historical times. Astronomy and
 *         Astrophysics, vol. 190, 1988, pp. 342-352.
 *      3) M. Chapront-Touzé, J. Chapront, G. Francou. Lunar solution ELP
 *         version ELP 2000-82B. Observatoire de Paris, 2001 (1985).
 *      4) J. Chapront and G. Francou. The lunar theory ELP revisited.
 *         Introduction of new planetary perturbations. Astronomy and
 *         Astrophysics, vol. 404, 2003, pp. 735-742.
 */

#ifndef ELP2000_H
#define ELP2000_H

/*
 * A datatype defining spherical coordiantes point consisting of
 * longitude, latitude and radial distance (altitude).
 */
typedef struct {
    double longitude;   // longitude (azimuth)
    double latitude;    // latitude (elevation)
    double distance;    // radial distance
} sphpoint;

/*
 * A datatype defining a point in three dimensional cartesian coordinate
 * system (x, y, z).
 */
typedef struct {
    double x;
    double y;
    double z;
} recpoint;

/*
 * Computes geocentric position of the Moon in spherical coordiantes
 * (longitude, latitude, distance) referred to the ELP2000 reference frame.
 * Input value t is the amount of Julian centuries since the beginning of
 * the epoch J2000.
 * Output longitude and latitude are measured in arcseconds and radial
 * distance is measured in kilometers.
 *
 * Source: M. Chapront-Touzé, J. Chapront, G. Francou. Lunar Solution
 *         ELP version ELP 2000-82B, 2001 (1985), p. 10.
 */
sphpoint geocentric_moon_position(double t);

/*
 * Computes geocentric position of the Moon in three dimentional cartesian
 * coordiantes (x, y, z) refered to the ELP2000 reference frame.
 * Input value t is the amount of Julian centuries since the beginning of
 * the epoch J2000.
 * All output values are measured in kilometers.
 *
 * Source: M. Chapront-Touzé, J. Chapront, G. Francou. Lunar Solution
 *         ELP version ELP 2000-82B, 2001 (1985), p. 10.
 */
recpoint geocentric_moon_position_rect(double t);

/*
 * Computes geocentric position of the Moon in three dimentional cartesian
 * coordiantes (x, y, z) refered to the mean ecliptic and equinox of J2000.
 * Input value t is the amount of Julian centuries since the beginning of
 * the epoch J2000.
 * All output values are measured in kilometers.
 *
 * Source: M. Chapront-Touzé, J. Chapront, G. Francou. Lunar Solution
 *         ELP version ELP 2000-82B, 2001 (1985), pp. 10-11.
 */
recpoint geocentric_moon_position_of_J2000(double t);

/*
 * Computes geocentric position of the Moon in three dimentional cartesian
 * coordiantes (x, y, z) refered to the FK5 equator (mean equator and 
 * rotational mean equinox of J2000).
 * Input value t is the amount of Julian centuries since the beginning of
 * the epoch J2000.
 * All output values are measured in kilometers.
 *
 * Source: M. Chapront-Touzé, J. Chapront, G. Francou. Lunar Solution
 *         ELP version ELP 2000-82B, 2001 (1985), p. 10-11.
 */
recpoint geocentric_moon_position_FK5(double t);

#endif // ELP2000_H