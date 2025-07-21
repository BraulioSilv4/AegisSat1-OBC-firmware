import serial
import time

# --- Global state variables ---
data_lines = []
current_line_index = 0
current_nmea_sentence = ""

# --- Timer for updating the sentence ---
previous_update_time = 0
update_interval = 30  # 30 seconds


def convert_dd_to_dmm(dd_in, is_lat):
    """Converts Decimal Degrees to Degrees Decimal Minutes format."""
    dd = abs(dd_in)
    deg = int(dd)
    minutes = (dd - deg) * 60.0

    if is_lat:
        hemisphere = 'N' if dd_in >= 0 else 'S'
        return f"{deg:02d}{minutes:08.5f}", hemisphere
    else:
        hemisphere = 'E' if dd_in >= 0 else 'W'
        return f"{deg:03d}{minutes:08.5f}", hemisphere


def calculate_checksum(sentence):
    """Calculates the NMEA checksum for a sentence."""
    checksum = 0
    for char in sentence:
        checksum ^= ord(char)
    return f"{checksum:02X}"


def update_current_nmea_sentence():
    """Updates the global NMEA sentence variable from the next CSV line."""
    global current_line_index, current_nmea_sentence, data_lines

    if current_line_index >= len(data_lines):
        print("\n--- End of data reached. Looping back to start. ---\n")
        current_line_index = 0

    line = data_lines[current_line_index].strip()
    current_line_index += 1

    if not line:
        return

    try:
        # Get all required parts from the CSV line
        parts = line.split(',')
        gregorian_str = parts[0]
        altitude_km_str = parts[2]  # Get the 3rd column (Altitude in km)
        latitude_dec = float(parts[3])
        longitude_dec = float(parts[4])
    except (ValueError, IndexError):
        print(f"Skipping malformed line: {line}")
        return

    # --- Perform NMEA Conversions ---
    time_part = gregorian_str.split(' ')[-1]
    hhmmss = time_part.split('.')[0].replace(":", "")
    ss_decimal = time_part.split('.')[1][:2]
    utc_time = f"{hhmmss}.{ss_decimal}"

    lat_nmea, lat_hemisphere = convert_dd_to_dmm(latitude_dec, is_lat=True)
    lon_nmea, lon_hemisphere = convert_dd_to_dmm(longitude_dec, is_lat=False)

    # --- CHANGE: Convert altitude from CSV (km) to meters ---
    altitude_m = float(altitude_km_str) * 1000.0

    # --- Assemble the sentence BODY ---
    # The format specifier {altitude_m:08.1f} ensures the 8-character width.
    nmea_body = (f"GPGGA,{utc_time},{lat_nmea},{lat_hemisphere},"
                 f"{lon_nmea},{lon_hemisphere},1,07,1.26,{altitude_m:08.1f},M,48.3,M,,")

    # --- Generate the final sentence with checksum ---
    checksum = calculate_checksum(nmea_body)
    current_nmea_sentence = f"${nmea_body}*{checksum}"


def main():
    """Main function to run the NMEA sender."""
    global previous_update_time, data_lines

    try:
        with open("Aegis_GPS.csv", "r") as f:
            all_file_lines = f.readlines()
            if not all_file_lines:
                print("Error: CSV file is empty.")
                return
            # Skip the header line
            data_lines = all_file_lines[1:]
        print(f"Successfully loaded {len(data_lines)} data lines from Aegis_GPS.csv")
    except FileNotFoundError:
        print("Error: 'Aegis_GPS.csv' not found. Make sure it's in the same directory.")
        return
    except Exception as e:
        print(f"An error occurred while reading the file: {e}")
        return

    try:
        # Replace 'COM8' with your actual serial port if different
        ser = serial.Serial('COM8', 9600, timeout=1)
        print("--- NMEA Continuous Looping Sender Initialized ---")
        print(f"Connected to {ser.name}")
        print(f"Updating sentence every {update_interval} seconds.")
        print()
    except serial.SerialException as e:
        print(f"Error opening serial port 'COM8': {e}")
        return

    # Generate the first sentence immediately
    update_current_nmea_sentence()
    previous_update_time = time.time()

    try:
        while True:
            if time.time() - previous_update_time >= update_interval:
                previous_update_time = time.time()
                update_current_nmea_sentence()

            if current_nmea_sentence:
                ser.write(current_nmea_sentence.encode('ascii') + b'\r\n')
                print(current_nmea_sentence)  # Optional: print to console

            time.sleep(0.1)

    except KeyboardInterrupt:
        print("\n--- Program terminated by user ---")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("Serial port closed.")


if __name__ == "__main__":
    main()