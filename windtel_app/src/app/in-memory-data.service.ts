import { InMemoryDbService } from 'angular-in-memory-web-api';
import { User } from './user';
import { Experiment } from './experiment';
import { Measurement } from './measurement';
import { PressurePoint } from './pressure-point';
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class InMemoryDataService implements InMemoryDbService {
  createDb() {
    const users = [
      { id: 1, first: 'Misael', last: 'Valentin', email: 'misael.valentin@upr.edu', vocation: 'Student', department: 'ICOM', institution: 'UPRM', city: 'Aguadilla', password: '12345678', permissions: 'Researcher' },
      { id: 2, first: 'Raúl', last: 'Zapata', email: 'raul.zapata@upr.edu', vocation: 'Professor', department: 'INCI', institution: 'UPRM', city: 'Cabo Rojo', password: '12345678', permissions: 'Administrator' },
      { id: 3, first: 'Ivan', last: 'Santiago', email: 'ivan.santiago@upr.edu', vocation: 'Technician', department: 'INCI', institution: 'UPRM', city: 'Juana Díaz', password: '12345678', permissions: 'Technician' },
      { id: 4, first: 'Nelson', last: 'Rodríguez', email: 'nelson.rodriguez21@upr.edu', vocation: 'Student', department: 'INEL', institution: 'UPRM', city: 'Lajas', password: '12345678', permissions: 'Pending' },
      { id: 5, first: 'Admin', last: 'Zapata', email: 'admin@upr.edu', vocation: 'Professor', department: 'INCI', institution: 'UPRM', city: 'San Juan', password: 'adminpass', permissions: 'Administrator' },
      { id: 6, first: 'Technician', last: 'Santiago', email: 'technician@upr.edu', vocation: 'Technician', department: 'INCI', institution: 'UPRM', city: 'San Juan', password: 'technicianpass', permissions: 'Technician' }
    ];
    const experiments = [
      { id: 1, name: 'my_first_experiment', description: 'This was my first experiment!', time: '5 minutes', date: '4/1/2019', userid: 1 }
    ];
    const measurements = [
      { id: 1, liftforce: '2 lb', dragfrontforce: '1 lb', dragbackfroce: '4 lb', leftsideforce: '3 lb', rightsideforce: '4 lb', windspeed: '5 mph', temperature: '23 C', humidity: '35%', experimentid: 1 },
      { id: 2, liftforce: '2 lb', dragfrontforce: '2 lb', dragbackfroce: '4 lb', leftsideforce: '3 lb', rightsideforce: '10 lb', windspeed: '10 mph', temperature: '23 C', humidity: '34%', experimentid: 1 },
      { id: 3, liftforce: '3 lb', dragfrontforce: '3 lb', dragbackfroce: '4 lb', leftsideforce: '3 lb', rightsideforce: '20 lb', windspeed: '15 mph', temperature: '23 C', humidity: '37%', experimentid: 1 },
      { id: 4, liftforce: '5 lb', dragfrontforce: '4 lb', dragbackfroce: '4 lb', leftsideforce: '3 lb', rightsideforce: '15 lb', windspeed: '20 mph', temperature: '23 C', humidity: '35%', experimentid: 1 },
      { id: 5, liftforce: '1 lb', dragfrontforce: '5 lb', dragbackfroce: '4 lb', leftsideforce: '3 lb', rightsideforce: '4 lb', windspeed: '25 mph', temperature: '23 C', humidity: '36%', experimentid: 1 }
    ];
    const pressurePoint = [
      { id: 1, point: '20 P', sensorNum: 1, measurementid: 1 },
      { id: 2, point: '20 P', sensorNum: 2, measurementid: 2 },
      { id: 3, point: '20 P', sensorNum: 3, measurementid: 3 },
      { id: 4, point: '20 P', sensorNum: 4, measurementid: 4 }
    ]
    return {users, experiments, measurements, pressurePoint};
  }

  genUserId(users: User[]): number {
    return users.length > 0 ? Math.max(...users.map(user => user.id)) + 1 : 1;
  }

  genExperimentId(experiments: Experiment[]): number {
    return experiments.length > 0 ? Math.max(...experiments.map(experiment => experiment.id)) + 1 : 1;
  }

  genMeasurementId(measurements: Measurement[]): number {
    return measurements.length > 0 ? Math.max(...measurements.map(measurement => measurement.id)) + 1 : 1;
  }

  genPressurePointId(pressurePoints: PressurePoint[]): number {
    return pressurePoints.length > 0 ? Math.max(...pressurePoints.map(pressurePoint => pressurePoint.id)) + 1 : 1;
  }
}
