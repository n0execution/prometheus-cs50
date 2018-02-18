//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

//height and width of paddle
#define P_HEIGHT 17
#define P_WIDTH 70

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 12

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    updateScoreboard(window,label, points); 
                    

    //velocity of ball
    double x_offset = 0.3;
    double y_offset = 0.31;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        //the movement of the paddle
        /////////////////////////////////////////////////
        GEvent event = getNextEvent(MOUSE_EVENT);

        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
                setLocation(paddle, x, HEIGHT * (7./8));
            }
        }
        //////////////////////////////////////////////////
        
        
        // movement of the ball
        /////////////////////////////////////////////////
        move(ball, x_offset, y_offset);
        
        // ball off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            x_offset = -x_offset;
        }

        // ball off left edge of window
        else if (getX(ball) <= 0)
        {
            x_offset = -x_offset;
        }
        
        // ball off the bottom of the window
        if (getY(ball) + getHeight(ball) >= getY(paddle) + 40)
        {
            lives--;
            if (lives != 0)
            {
                waitForClick();
                setLocation(ball, WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS);
            }
        }
        
        // ball off the top of te window
        else if (getY(ball) <= 0)
        {
            y_offset = -y_offset;
        }
        ///////////////////////////////////////////////////
        
        
        // checking collision
        ///////////////////////////////////////////////////
        GObject object = detectCollision(window, ball);
        if (object != NULL)
            if (strcmp(getType(object), "GRect") == 0)
            {
                if (object == paddle)
                {
                    y_offset = -y_offset;
                }
                else 
                {
                    y_offset = -y_offset;
                    points++;
                    updateScoreboard(window,label, points); 
                    bricks--;
                    removeGWindow(window, object);
                }
            }
        ///////////////////////////////////////////////////
        
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    float brick_width = 35.6;
    float brick_height = 10;
    char* color[5];
    color[0] = "RED";
    color[1] = "ORANGE";
    color[2] = "YELLOW";
    color[3] = "GREEN";
    color[4] = "CYAN";
    int offset[10];
    for (int k = 0; k < 10; k++)
        offset[k] = (k + 1) * 4;
    GRect brick[ROWS][COLS];
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            brick[i][j] = newGRect(brick_width * j + offset[j], 40 + brick_height * i + offset[i], brick_width, brick_height);
            setFilled(brick[i][j], true);
            setColor(brick[i][j], color[i]);
            add(window, brick[i][j]);
        }
    }    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval circle = newGOval(WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS, 2 * RADIUS, 2 * RADIUS);
    setFilled(circle, true);
    setColor(circle, "BLACK");
    add(window, circle); 
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(WIDTH / 2 - P_WIDTH / 2, HEIGHT * (7./8), P_WIDTH, P_HEIGHT); 
    setFilled(paddle, true);
    setColor(paddle, "BLUE");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    add(window, label);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
