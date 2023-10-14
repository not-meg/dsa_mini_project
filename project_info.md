# dsa_mini_project
# travel itinerary project for dsa using graphs and trees in c

## what we have (data):
### 1. flight itinerary csv file, containing:
- from location
- to location
- price of flight
- duration of flight
- distance between [from] and [to]
- agency (is this required?)

### 2. hotel list csv file, containing:
- travel code (is this required?)
- userCode (is this required?)
- hotel name (for now, each hotel name is a 6-letter randomly generated name)
- place ([to] location)
- price per day

## what we need to implement

- [ ] Reading data from csv files and storing them in an array / linked list
- [ ] Requesting data from the user, specifically,
  - Name (is this required?)
  - Source location
  - Destination
  - Number of days of travel
  - Ask user:
    - if they want to add any stops
    - for flight, do they want less time or less cost
    - for hotel, do they want most popular (based on ratings) or less cost
  - Sort flight data according to user's preference and return
  - Sort hotel data according to user's preference and return
  - print an itinerary based on all the data collected
