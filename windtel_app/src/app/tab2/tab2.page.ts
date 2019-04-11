import { Component } from '@angular/core';

import { Experiment } from '../experiment';
import { UserService } from '../user.service';
import { User } from '../user';

@Component({
  selector: 'app-tab2',
  templateUrl: 'tab2.page.html',
  styleUrls: ['tab2.page.scss']
})
export class Tab2Page {

  currentUser: User;
  permissions: string;

  model = new Experiment(1, 'my_first_experiment', 'This is my first experiment!', '15 seconds', '4/11/2019', 1, 10);

  constructor(private userService: UserService) { }

  getCurrentUser() {
    this.currentUser = this.userService.getCurrentUser();
    this.permissions = this.currentUser.permissions;
  }

  tryExperimentStart() {
    // TODO
  }

  ngOnInit() { }

}
