# ThingSpeak Dashboard Setup Guide

## Overview
This guide explains how to set up a ThingSpeak dashboard to visualize the data from your smart waste bin monitoring system. ThingSpeak is an IoT analytics platform that allows you to collect, visualize, and analyze live data streams in the cloud.

## Creating a ThingSpeak Account
1. Go to [ThingSpeak](https://thingspeak.com/) and sign up for a free account
2. After signing in, click on "My Channels" and then "New Channel"

## Setting Up Your Channel
1. Fill in the following information:
   - Name: Smart Waste Bin Monitor
   - Description: Monitors the fill level of a waste bin using an ultrasonic sensor
   - Field 1: Distance (cm)
   - Field 2 (optional): Status (0 for empty, 1 for full)
2. Click "Save Channel"

## Getting Your API Keys
1. After creating the channel, go to the "API Keys" tab
2. Note your "Write API Key" - this is what you'll use in your Arduino code
3. Replace the placeholder API key in the code with your actual key:
   ```cpp
   String apiKey = "YOUR_API_KEY_HERE"; // Replace with your ThingSpeak API key
   ```

## Creating Visualizations
1. Go to the "Private View" tab of your channel
2. Click "Add Widgets" to add visualizations
3. Recommended widgets:
   - **Line Chart**: Shows distance measurements over time
   - **Gauge**: Shows current fill level
   - **Status Indicator**: Shows whether the bin is full or has space

## Setting Up Alerts (Optional)
1. Go to the "Apps" tab in ThingSpeak
2. Select "ThingSpeak Alerts"
3. Create a new alert with these settings:
   - Test Frequency: Every hour (or as needed)
   - Condition: Field 1 < 10 (or your threshold for "full")
   - Action: Email or other notification

## Viewing Your Dashboard
1. Go to the "Private View" tab to see your dashboard
2. You can share a public view by enabling it in the "Sharing" tab

## Troubleshooting
- If no data appears in ThingSpeak, check:
  - Your Wi-Fi connection
  - API key correctness
  - ThingSpeak server status
- If data is inconsistent, check the update interval in your code

## Mobile App Access
1. Download the ThingSpeak mobile app from the App Store or Google Play
2. Log in with your ThingSpeak account
3. Access your channel to view real-time data from your waste bin

## Data Analysis
ThingSpeak provides MATLAB analysis capabilities. You can create custom analyses to:
- Predict when the bin will be full based on historical data
- Analyze usage patterns
- Optimize waste collection schedules