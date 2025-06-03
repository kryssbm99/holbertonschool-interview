#!/usr/bin/node
// This script prints all characters from a Star Wars movie using the API

const request = require('request');

// Get the movie ID from the command line
const movieId = process.argv[2];

// Check if a valid ID was given
if (!movieId || isNaN(parseInt(movieId))) {
  console.error('Usage: ./0-starwars_characters.js <Movie ID>');
  process.exit(1);
}

// URL to get the movie details
const filmUrl = `https://swapi.dev/api/films/${movieId}/`;

// Set request settings
const requestOptions = {
  url: filmUrl,
  strictSSL: false
};

// Request movie info
request(requestOptions, (error, response, body) => {
  if (error) {
    console.error('Failed to get movie:', error);
    process.exit(1);
  }

  if (response.statusCode !== 200) {
    console.error(`Failed with status code ${response.statusCode}`);
    process.exit(1);
  }

  try {
    // Convert the response to an object
    const filmData = JSON.parse(body);
    const characterUrls = filmData.characters;

    if (!characterUrls || characterUrls.length === 0) {
      process.exit(0); // No characters to show
    }

    const characterNames = new Array(characterUrls.length);
    let charactersProcessed = 0;
    const totalCharacters = characterUrls.length;

    // Get character name and save it in order
    const fetchCharacter = (url, index) => {
      const charRequestOptions = {
        url,
        strictSSL: false
      };
      request(charRequestOptions, (charError, charResponse, charBody) => {
        if (!charError && charResponse.statusCode === 200) {
          try {
            const characterData = JSON.parse(charBody);
            characterNames[index] = characterData.name;
          } catch (parseErr) {
            console.error(`Failed to read data from ${url}:`, parseErr);
          }
        } else {
          console.error(`Problem with character ${url}:`, charError || `Code ${charResponse?.statusCode || 'N/A'}`);
        }

        charactersProcessed++;

        // When all are done, show the results
        if (charactersProcessed === totalCharacters) {
          characterNames.forEach(name => {
            if (name) console.log(name);
          });
        }
      });
    };

    // Loop through all characters and start requests
    characterUrls.forEach((url, index) => {
      fetchCharacter(url, index);
    });
  } catch (parseError) {
    console.error('Could not process movie data:', parseError);
    process.exit(1);
  }
});
