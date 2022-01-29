-- Keep a log of any SQL queries you execute as you solve the mystery.

-- find out the schema, save it
.shema

-- find out how to enable logging
.help

-- try to enable log(1) near "%": syntax error in "SELECT * FROM interviews WHERE year >= 2021 AND transcript LIKE %bakery%;"
 query logging

-- find crime scene report
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street"; 
-- | 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |

-- suspects: (any) two people on a plance after the robbery

-- find the mentioned witness interviews
SELECT * FROM interviews WHERE year >= 2021 AND transcript LIKE "%bakery%"; -- close enough: the three relevant-sounding interviews have adjacent ids and were all conducted on the 28. July and describe a robbery: 
-- | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- takeaways: check security footage 10m after (10:15am was the theft) and look for a car leaving, check ATM withdrawals morning same day on Leggett Street, check phone logs that morning for a phone call less than 1m, flight planned to take on 29. July out of Fiftyville and accomplice should buy tickets

-- find security logs of that day
SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute <=25 AND activity = "exit"; 
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | id  | year | month | day | hour | minute | activity | license_plate |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
-- | 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
-- | 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
-- | 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
-- | 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
-- | 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
-- | 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
-- | 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
-- | 268 | 2021 | 7     | 28  | 10   | 35     | exit     | 1106N58       |
-- +-----+------+-------+-----+------+--------+----------+---------------+

-- suspects: people with these license plates: (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND activity = "exit")

-- find ATM withdrawal same morning
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
-- | 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
-- | 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
-- | 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
-- | 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
-- | 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+

-- suspects: people with these account numbers: (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw")

-- find phone call that morning less than 1m
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60;
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | id  |     caller     |    receiver    | year | month | day | duration |
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
-- | 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
-- | 234 | (609) 555-5876 | (389) 555-5198 | 2021 | 7     | 28  | 60       |
-- | 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
-- | 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
-- | 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
-- | 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
-- | 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
-- +-----+----------------+----------------+------+-------+-----+----------+

-- suspects: people with these phone numbers: (SELECT caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60) caller is the thief and receiver the accomplice

-- find flight on 29. july out of Fiftyville
SELECT * FROM flights, airports WHERE airports.id = flights.origin_airport_id AND year = 2021 AND month = 7 AND day = 29 AND city = "Fiftyville";
-- id|origin_airport_id|destination_airport_id|year|month|day|hour|minute|id|abbreviation|full_name|city
-- 18|8|6|2021|7|29|16|0|8|CSF|Fiftyville Regional Airport|Fiftyville
-- 23|8|11|2021|7|29|12|15|8|CSF|Fiftyville Regional Airport|Fiftyville
-- 36|8|4|2021|7|29|8|20|8|CSF|Fiftyville Regional Airport|Fiftyville
-- 43|8|1|2021|7|29|9|30|8|CSF|Fiftyville Regional Airport|Fiftyville
-- 53|8|9|2021|7|29|15|20|8|CSF|Fiftyville Regional Airport|Fiftyville

-- find passports of passengers on these flights
SELECT DISTINCT(passport_number) FROM passengers, flights WHERE passengers.flight_id = flights.id AND flights.id IN (SELECT flights.id FROM flights, airports WHERE airports.id = flights.origin_airport_id AND year = 2021 AND month = 7 AND day = 29 AND city = "Fiftyville");
-- 2835165196
-- 6131360461
-- ...
SELECT COUNT(DISTINCT(passport_number)) FROM passengers, flights WHERE passengers.flight_id = flights.id AND flights.id IN (SELECT flights.id FROM flights, airports WHERE airports.id = flights.origin_airport_id AND year = 2021 AND month = 7 AND day = 29 AND city = "Fiftyville");
-- 37

-- SUMMARY suspects: 
-- people with these license plates: (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND activity = "exit")
-- people with these phone numbers: (SELECT caller, receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60) caller is the thief and receiver the accomplice
-- people with these account numbers: (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw")
-- people with that passport numbers: (SELECT DISTINCT(passport_number) FROM passengers, flights WHERE passengers.flight_id = flights.id AND flights.id IN (SELECT flights.id FROM flights, airports WHERE airports.id = flights.origin_airport_id AND year = 2021 AND month = 7 AND day = 29 AND city = "Fiftyville"))

-- find possible thief suspects with bank_accounts
SELECT * FROM people, bank_accounts WHERE people.id = bank_accounts.person_id AND bank_accounts.account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND activity = "exit") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60) AND passport_number IN (SELECT DISTINCT(passport_number) FROM passengers, flights WHERE passengers.flight_id = flights.id AND flights.id IN (SELECT flights.id FROM flights, airports WHERE airports.id = flights.origin_airport_id AND year = 2021 AND month = 7 AND day = 29 AND city = "Fiftyville"));
-- id|name|phone_number|passport_number|license_plate|account_number|person_id|creation_year
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X|49610011|686048|2010
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE|26013199|514354|2012
-- 449774|Taylor|(286) 555-6063|1988161715|1106N58|76054385|449774|2015

-- find possible accomplice suspects without bank account (did not do a withdrawal we know of) and without license plate (accomplice wasn't on site) and without taking a plane (no info on that)
SELECT * FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60);
-- id|name|phone_number|passport_number|license_plate
-- 250277|James|(676) 555-6554|2438825627|Q13SVG6
-- 251693|Larry|(892) 555-8872|2312901747|O268ZZ0
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 484375|Anna|(704) 555-2131||
-- 567218|Jack|(996) 555-8899|9029462229|52R0Y8U
-- 626361|Melissa|(717) 555-1342|7834357192|
-- 712712|Jacqueline|(910) 555-3251||43V0R5D
-- 847116|Philip|(725) 555-3243|3391710505|GW362R6
-- 864400|Robin|(375) 555-8161||4V16VO0
-- 953679|Doris|(066) 555-9701|7214083635|M51FA04

-- find if any of the thief suspects called the accomplice suspects
SELECT * FROM phone_calls WHERE caller IN (SELECT phone_number FROM people, bank_accounts WHERE people.id = bank_accounts.person_id AND bank_accounts.account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND activity = "exit") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60) AND passport_number IN (SELECT DISTINCT(passport_number) FROM passengers, flights WHERE passengers.flight_id = flights.id AND flights.id IN (SELECT flights.id FROM flights, airports WHERE airports.id = flights.origin_airport_id AND year = 2021 AND month = 7 AND day = 29 AND city = "Fiftyville"))) AND receiver IN (SELECT phone_number FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60));
-- id|caller|receiver|year|month|day|duration
-- 233|(367) 555-5533|(375) 555-8161|2021|7|28|45
-- 254|(286) 555-6063|(676) 555-6554|2021|7|28|43
-- 255|(770) 555-1861|(725) 555-3243|2021|7|28|49

-- find caller and receiver of call with plates of cars leaving max. 10 min into theft 
SELECT * FROM phone_calls WHERE caller IN (SELECT phone_number FROM people, bank_accounts WHERE people.id = bank_accounts.person_id AND bank_accounts.account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60) AND passport_number IN (SELECT DISTINCT(passport_number) FROM passengers, flights WHERE passengers.flight_id = flights.id AND flights.id IN (SELECT flights.id FROM flights, airports WHERE airports.id = flights.origin_airport_id AND year = 2021 AND month = 7 AND day = 29 AND city = "Fiftyville"))) AND receiver IN (SELECT phone_number FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60));
-- id|caller|receiver|year|month|day|duration
-- 233|(367) 555-5533|(375) 555-8161|2021|7|28|45
-- 255|(770) 555-1861|(725) 555-3243|2021|7|28|49

-- going back to the beginning and re-checking witness statements
SELECT * FROM interviews WHERE year >= 2021 AND transcript LIKE "%bakery%";
-- id|name|year|month|day|transcript
-- 161|Ruth|2021|7|28|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162|Eugene|2021|7|28|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- 163|Raymond|2021|7|28|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
-- 192|Kiana|2021|5|17|I saw Richard take a bite out of his pastry at the bakery before his pastry was stolen from him.
-- 193|Emma|2021|7|28|I'm the bakery owner, and someone came in, suspiciously whispering into a phone for about half an hour. They never bought anything.
-- additional takeaways: "earliest" flight tomorrow, and Emma said someone talked for 30min on the phone without buying anything ... (could be nothing)

-- find EARLIEST flight on 29. july out of Fiftyville
SELECT * FROM flights, airports WHERE airports.id = flights.origin_airport_id AND year = 2021 AND month = 7 AND day = 29 AND city = "Fiftyville" ORDER BY hour, minute LIMIT 1;
-- id|origin_airport_id|destination_airport_id|year|month|day|hour|minute|id|abbreviation|full_name|city
-- 36|8|4|2021|7|29|8|20|8|CSF|Fiftyville Regional Airport|

-- find caller and receiver of call with all info
SELECT * FROM phone_calls WHERE caller IN (SELECT phone_number FROM people, bank_accounts WHERE people.id = bank_accounts.person_id AND bank_accounts.account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw") AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit") AND phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60) AND passport_number IN (SELECT DISTINCT(passport_number) FROM passengers, flights WHERE passengers.flight_id = flights.id AND flights.id IN (SELECT flights.id FROM flights, airports WHERE airports.id = flights.origin_airport_id AND year = 2021 AND month = 7 AND day = 29 AND city = "Fiftyville" ORDER BY hour, minute LIMIT 1))) AND receiver IN (SELECT phone_number FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration <= 60));
-- id|caller|receiver|year|month|day|duration
-- 233|(367) 555-5533|(375) 555-8161|2021|7|28|45

-- look up thief name
SELECT * FROM people WHERE phone_number = "(367) 555-5533";
-- id|name|phone_number|passport_number|license_plate
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X

-- look up accomplice name
SELECT * FROM people WHERE phone_number = "(375) 555-8161";
-- id|name|phone_number|passport_number|license_plate
-- 864400|Robin|(375) 555-8161||4V16VO0

-- look up destination of escape flight
SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM airports, flights WHERE airports.id = flights.origin_airport_id AND year = 2021 AND month = 7 AND day = 29 AND city = "Fiftyville" ORDER BY hour, minute LIMIT 1);
-- city
-- New York City