//
//  Inventory.cpp
//  Program4
//
//  Created by Jay Brar & Jose Palomera
//  Copyright © 2020 Jay Brar & Jose Palomera. All rights reserved.
//

#include <stdio.h>
#include "Inventory.h"

Inventory::Inventory(){}

Inventory::~Inventory()
{
    DeleteMovies();
}

void Inventory::buildInventory(string const &movieFile)
{
    //Create a new file reader
    ifstream movies(movieFile);
    if(!movies)
    {
        cerr << "ERROR: Invalid input file" << endl;
        return;
    }
    //While the file still has lines
    while(!movies.eof())
    {
            
        char type;
        //Retrieve what type of movie we want to create
        movies >> type;
        
        switch(type)
        {
            //If the letter is C
            case 'C':
            {
                //Create a new Classic movie object
                Classic *c = new Classic();
                c->setData(movies);
                //And place in the vector of Classic movies
                classics.push_back(*c);
                break;
            }
            //If the letter is F
            case 'F':
            {
                //Create a new Comedy movie object
                Comedy *f = new Comedy();
                f->setData(movies);
                //And place in the vector of Comedy movies
                comedies.push_back(*f);
                break;
            }
            //If the letter is D
            case 'D':
            {
                //Create a new Drama movie object
                Drama *d = new Drama();
                d->setData(movies);
                //And place in the vector of Drama movies
                dramas.push_back(*d);
                break;
            }
            //If the letter is something else
            default:{
                //Alert the business of an invalid movie
                cerr << "ERROR: Invalid movie type " << type << endl;
                movies.ignore(1000000, '\n');
                break;
            }
        }
        
    }
    
}

void Inventory::viewClassics()
{
    //Loop that goes through the Classics vector and displays the movies
    for(int i = 0;i < classics.size(); i++)
    {
        classics[i].display();
    }
    
    cout << endl;
}

void Inventory::viewComedies()
{
    //Loop that goes through the Comedies vector and displays the movies
    for(int i = 0;i < comedies.size(); i++)
    {
        comedies[i].display();
    }
    
    cout << endl;
}

void Inventory::viewDramas()
{
    //Loop that goes through the Dramas vector and displays the movies
    for(int i = 0;i < dramas.size(); i++)
    {
        dramas[i].display();
    }
    
    cout << endl;
}

void Inventory::viewInventory()
{
    cout << "Comedies:" << endl;
    viewComedies();
    
    cout << "Dramas:" << endl;
    viewDramas();
    
    cout << "Classics:" << endl;
    viewClassics();
    
}

// HAS WEIRD CASE
bool Inventory::findClassicMovie(int releaseMonth, int releaseYear, string majorActor, Movie *&selection)
{
    // Searching through the classic movie vector to find the desired movie
    for (int i = 0; i < classics.size(); i++)
    {
            // If we locate the desired movie
            if (releaseMonth == classics[i].getReleaseMonth() && releaseYear == classics[i].getReleaseYear()
                && majorActor == classics[i].getMajorActor())
            {
                // Return false if it is out of stock
                if (classics[i].getStock() == 0)
                {
                    cerr << "ERROR: Desired movie out of stock" << endl;
                    findClassicDuplicate(classics[i].getTitle(), classics[i].getMajorActor());
                    // FIND OUT IF THERE IS ANOTHER ONE
                    return false;
                }
                // In stock so we send the desired movie over and return true
                selection = &classics[i];
                return true;
            }
        }
    // No such movie in the database
        cerr << "ERROR: Movie not found in database" << endl;
    return false;
}

void Inventory::findClassicDuplicate(string title, string majorActor)
{
    // Searching through the classic movie vector to find an alternative movie
    for (int i = 0; i < classics.size(); i++)
    {
        // If there is the same movie with a different major actor in stock display a message
        if (title == classics[i].getTitle() && majorActor != classics[i].getMajorActor() && classics[i].getStock() > 0)
        {
            cout << "Alternative: ";
            classics[i].display();
            cout << endl;
            return;
        }
    }
}

bool Inventory::findComedyMovie(string title, int releaseYear, Movie *&selection)
{
    // Searching through the comedy movie vector to find the desired movie
    for (int i = 0; i < comedies.size(); i++)
    {
        // If we locate the desired movie
        if (title == comedies[i].getTitle() && releaseYear == comedies[i].getReleaseYear())
        {
            // Return false if it is out of stock
            if (comedies[i].getStock() == 0)
            {
                cerr << "ERROR: Movie out of stock" << endl;
                return false;
            }
            // In stock so we send the desired movie over and return true
            selection = &comedies[i];
            return true;
        }
    }
    // No such movie in the database
    cerr << "ERROR: Movie not found in database" << endl;
    return false;
}

bool Inventory::findDramaMovie(string director, string title, Movie *&selection)
{
    // Searching through the drama movie vector to find the desired movie
    for (int i = 0; i < dramas.size(); i++)
    {
        // If we locate the desired movie
        if (director == dramas[i].getDirector() && title == dramas[i].getTitle())
        {
            // Return false if it is out of stock
            if (dramas[i].getStock() == 0)
            {
                cerr << "ERROR: Movie out of stock" << endl;
                return false;
            }
            // In stock so we send the desired movie over and return true
            selection = &dramas[i];
            return true;
        }
    }
    // No such movie in the database
    cerr << "ERROR: Movie not found in database" << endl;
    return false;
}

void Inventory::DeleteMovies()
{
    for (int i = 0; i < classics.size(); i++)
    {
        
    }

    for (int j = 0; j < comedies.size(); j++)
    {
        
    }

    for (int k = 0; k < dramas.size(); k++)
    {
        
    }
}
