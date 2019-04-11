import { Component } from '@angular/core';
import { Experiment } from '../experiment';

@Component({
  selector: 'app-tab2',
  templateUrl: 'tab2.page.html',
  styleUrls: ['tab2.page.scss']
})
export class Tab2Page {

  model = new Experiment(1, 'my_first_experiment', 'This is my first experiment!', '15 seconds', '4/11/2019', 1, 10);

  tryExperimentStart() {
    // TODO
  }
}
