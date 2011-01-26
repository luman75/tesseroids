/* *****************************************************************************
Copyright 2011 Leonardo Uieda

Tesseroids is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Tesseroids is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Tesseroids.  If not, see <http://www.gnu.org/licenses/>.
***************************************************************************** */

/* *****************************************************************************
Unit tests for GLQ functions.

Author: Leonardo Uieda
Date: 24 Jan 2011
***************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "minunit.h"
#include "../src/c/utils.h"
#include "../src/c/constants.h"

/* To store fail messages */
char msg[1000];

/* FIXTURES */
#define NTESSES 4
TESSEROID tesses[NTESSES] = {
    {0,0,1,0,1,6000000,6001000},
    {0,80,85,180,190,6300000,6301000},
    {0,-90,-70,160,200,5500000,6000000},
    {0,-7,15,-10,5,6500000,6505000}};


/* UNIT TESTS */

static char * test_prism_volume()
{
    PRISM prisms[4] = {{0,0,1,0,1,0,1}, {0,0,2,0,1,0,1}, {0,0,2,0,2,0,2},
                       {0,1,2,-1,1,2,3}};
    double pvolumes[4] = {1, 2, 8, 2};
    double res;
    int i;

    for(i = 0; i < 4; i++)
    {
        res = prism_volume(prisms[i]);
        sprintf(msg, "(prism %d) expected %g, got %g", i, pvolumes[i], res);
        mu_assert(res == pvolumes[i], msg);
    }

    return 0;
}


static char * test_tess_volume()
{
    TESSEROID tesses[4] = {{0,-90,90,0,360,0,1}, {0,0,90,0,360,0,1},
                           {0,0,90,180,360,0,1}, {0,-90,0,0,90,0,1}};
    double tvolumes[4] = {4.188790205, 2.094395102, 1.047197551, 0.523598776};
    double res;
    int i;

    for(i = 0; i < 4; i++)
    {
        res = tess_volume(tesses[i]);
        sprintf(msg, "(tess %d) expected %g, got %g", i, tvolumes[i], res);
        mu_assert_almost_equals(res, tvolumes[i], pow(10, -8), msg);
    }

    return 0;
}


static char * test_tess2prism()
{
    double expect, res;
    PRISM prism;
    int i;

    for(i = 0; i <  NTESSES; i++)
    {
        tess2prism(tesses[i], &prism);
        res = prism_volume(prism);
        expect = tess_volume(tesses[i]);
        sprintf(msg, "(tess %d) expected volume %g, got %g", i, expect, res);
        mu_assert_almost_equals(res/expect, 1., 0.01, msg);
    }
    
    return 0;
}


static char * test_tess2sphere()
{
    double expect, res;
    SPHERE sphere;
    int i;

    for(i = 0; i <  NTESSES; i++)
    {
        tess2sphere(tesses[i], &sphere);
        res = sphere_volume(sphere);
        expect = tess_volume(tesses[i]);
        sprintf(msg, "(tess %d) expected volume %g, got %g", i, expect, res);
        mu_assert_almost_equals(res/expect, 1., 0.01, msg);
    }

    return 0;
}


void utils_run_all()
{
    mu_run_test(test_prism_volume, "prism_volume return correct results");
    mu_run_test(test_tess_volume, "tess_volume return correct results");
    mu_run_test(test_tess2prism, "tess2prism produces prism with right volume");
    mu_run_test(test_tess2sphere,
                "tess2sphere produces sphere with right volume");
}