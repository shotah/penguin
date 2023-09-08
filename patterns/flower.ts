// Description: A pattern for the LED matrix
import {white, blue, yellow} from './colors';

const backgroundColor = white;

export const flower = [
  // Line one
  [
    backgroundColor,
    backgroundColor,
    backgroundColor,
    blue,
    blue,
    backgroundColor,
    backgroundColor,
    backgroundColor,
  ],
  // Line two
  [
    backgroundColor,
    blue,
    blue,
    backgroundColor,
    backgroundColor,
    blue,
    blue,
    backgroundColor,
  ],
  // Line three
  [
    backgroundColor,
    blue,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    blue,
    backgroundColor,
  ],
  // Line four
  [
    blue,
    backgroundColor,
    backgroundColor,
    yellow,
    yellow,
    backgroundColor,
    backgroundColor,
    blue,
  ],
  // Line five
  [
    blue,
    backgroundColor,
    backgroundColor,
    yellow,
    yellow,
    backgroundColor,
    backgroundColor,
    blue,
  ],
  // Line six
  [
    backgroundColor,
    blue,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    backgroundColor,
    blue,
    backgroundColor,
  ],
  // Line seven
  [
    backgroundColor,
    blue,
    blue,
    backgroundColor,
    backgroundColor,
    blue,
    blue,
    backgroundColor,
  ],
  // Line eight
  [
    backgroundColor,
    backgroundColor,
    backgroundColor,
    blue,
    blue,
    backgroundColor,
    backgroundColor,
    backgroundColor,
  ],
];
