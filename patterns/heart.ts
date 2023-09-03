// Description: A heart pattern for the LED matrix

import {red, black} from './colors';

const backgroundColor = black;

export const heart = [
  // Line one
  [
    backgroundColor,
    red,
    red,
    backgroundColor,
    backgroundColor,
    red,
    red,
    backgroundColor,
  ],
  // Line two
  [
    red,
    backgroundColor,
    backgroundColor,
    red,
    red,
    backgroundColor,
    backgroundColor,
    red,
  ],
  // Line three
  [
    red,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    red,
  ],
  // Line four
  [
    red,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    red,
  ],
  // Line five
  [
    backgroundColor,
    red,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    red,
    backgroundColor,
  ],
  // Line six
  [
    backgroundColor,
    backgroundColor,
    red,
    backgroundColor,
    backgroundColor,
    red,
    backgroundColor,
    backgroundColor,
  ],
  // Line seven
  [
    backgroundColor,
    backgroundColor,
    backgroundColor,
    red,
    red,
    backgroundColor,
    backgroundColor,
    backgroundColor,
  ],
  // Line eight
  [
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
  ],
];
