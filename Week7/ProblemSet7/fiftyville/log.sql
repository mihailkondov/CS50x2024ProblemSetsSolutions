-- Keep a log of any SQL queries you execute as you solve the mystery.

.schema -- to see what kind of data I have in my hands

-- get crime reports from the day of the theft
SELECT id, description
FROM crime_scene_reports
WHERE year = 2023
AND month = 7
AND day = 28
AND street = 'Humphrey Street';

-- Now I know it took place at the bakery
-- Three witnesses who gave interviews
-- Littering took place, might be related?

-- Let's check the bakery logs at that date
.schema bakery_security_logs

SELECT hour, minute, activity, p.license_plate, name
FROM bakery_security_logs AS b, people AS p
WHERE p.license_plate = b.license_plate
AND year = 2023
AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 15 AND 25;

-- I am looking for the interviews of the 3 witnesses in the bakery
-- Using the info everyone mentions bakery in their interviews to
-- filter out the non-related interviews from the day.
SELECT id, name, transcript
FROM interviews
WHERE year = 2023
AND month = 7
AND day = 28
AND transcript LIKE '%bakery%';

/* Eugene saw the thief withdraw money before arriving to the bakery
I want to see when Eugene arrived at the bakery, so I can see who are
the people who withdrew money at the ATM before that.
*/

SELECT day, month, year, hour, minute, activity, p.license_plate, name
FROM bakery_security_logs AS b, people AS p
WHERE p.license_plate = b.license_plate
AND year = 2023
AND month = 7
AND day BETWEEN 27 AND 28
AND name = 'Eugene';
-- It appears that Eugene didn't come to the bakery by car
-- that day, or they used someone else's car

SELECT name, month, day, hour, minute
FROM bakery_security_logs, people
WHERE people.license_plate = bakery_security_logs.license_plate
AND people.name = 'Eugene';

-- list of suspects who exited the bakery 10 minutes after the incident
SELECT hour, minute, p.license_plate, b.activity, name
FROM bakery_security_logs AS b, people AS p
WHERE p.license_plate = b.license_plate
AND year = 2023
AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 15 AND 25;


-- This table gives the times of entrance of the suspects
SELECT hour, minute, p.license_plate, b.activity, name
FROM bakery_security_logs AS b, people AS p
WHERE p.license_plate = b.license_plate
AND year = 2023
AND month = 7
AND day = 28
AND (hour < 10 OR (hour = 10 AND minute BETWEEN 0 and 15))
AND b.activity = 'entrance'
AND b.license_plate in (
    SELECT p.license_plate
    FROM bakery_security_logs AS b, people AS p
    WHERE p.license_plate = b.license_plate
    AND year = 2023
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 15 AND 25);

/* lets chech the atm transactions between 7 and 9:28
on Leggett Street */
SELECT p.name, transaction_type, amount
FROM atm_transactions AS a
JOIN bank_accounts AS b ON b.account_number = a.account_number
JOIN people AS p ON b.person_id = p.id
WHERE a.year = 2023 AND month = 7 AND day = 28
AND transaction_type = 'withdraw';

/* Now I want to take only the ones who exited the parking lot*/
SELECT p.name, transaction_type, amount
FROM atm_transactions AS a
JOIN bank_accounts AS bank ON bank.account_number = a.account_number
JOIN people AS p ON bank.person_id = p.id
JOIN bakery_security_logs as bake ON p.license_plate = bake.license_plate
WHERE a.year = 2023 AND a.month = 7 AND a.day = 28
AND transaction_type = 'withdraw'
AND bake.license_plate in (
    SELECT p.license_plate
    FROM bakery_security_logs
    WHERE p.license_plate = bake.license_plate
    AND bake.year = 2023
    AND bake.month = 7
    AND bake.day = 28
    AND bake.hour = 10
    AND bake.minute BETWEEN 15 AND 25);

/*
Now let's see phone numbers and who talked for less than a minute
on the same day between 10:15 and 10:30.
*/

-- One of these two people is the thief and one of the receivers of the
-- call is the accessory
SELECT DISTINCT p.name, p.phone_number, phone.duration, phone.caller, phone.receiver
FROM people AS p
    JOIN bank_accounts AS bank ON bank.person_id = p.id
    JOIN atm_transactions AS a ON bank.account_number = a.account_number
    JOIN bakery_security_logs AS bake ON p.license_plate = bake.license_plate
    JOIN phone_calls as phone ON p.phone_number = phone.caller
WHERE  a.year = 2023 AND a.month = 7 AND a.day = 28
AND a.transaction_type = 'withdraw'
AND bake.license_plate in (
    SELECT p.license_plate
    FROM bakery_security_logs
    WHERE p.license_plate = bake.license_plate
    AND bake.year = 2023
    AND bake.month = 7
    AND bake.day = 28
    AND bake.hour = 10
    AND bake.minute BETWEEN 15 AND 25
    )
AND phone.receiver in (
    SELECT phone.receiver
    FROM phone_calls as phone
    WHERE phone.duration < 60
    AND phone.year = 2023
    AND phone.month = 7
    AND phone.day = 28
);

-- Flight taken by the suspect
SELECT fl.id, ap.full_name as origin, ap_dest.city as destination, hour, minute
FROM flights as fl
JOIN airports as ap ON ap.id = fl.origin_airport_id
JOIN airports as ap_dest ON ap_dest.id = fl.destination_airport_id
WHERE year = 2023 AND month = 7 AND day = 29
AND ap.full_name = 'Fiftyville Regional Airport'
ORDER BY hour, minute
LIMIT 1;

SELECT name
FROM people as pe, passengers as pa
WHERE pe.passport_number = pa.passport_number
AND flight_id = 36;

/* Figure out associate:
-> must have received a call on 28.07.2023
->
*/

SELECT pc.name as caller, pr.name as receiver
FROM phone_calls as calls
JOIN people AS pc ON pc.phone_number = calls.caller
JOIN people AS pr ON pr.phone_number = calls.receiver
WHERE pc.name = 'Bruce'
AND calls.year = 2023
AND calls.month = 7
AND calls.day = 28
AND calls.duration < 60;
