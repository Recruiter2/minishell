## Setting Up Your Branches

*Before creating a new branch, make sure you are up to date with the main branch. Simply:*

```sh
$ git pull origin main
```

Don’t ever work on the main branch. Let’s refresh your memories on how to make branches:

```sh
$ git checkout -b branchName
```

> Tip: Each branch should be made based on each feature, not page. For example, some branches could be:
> fbAuth,
> editUserInfo,
> addingGulp,
> etc.

When you make a branch, it's only created locally. So, we need to make it exist on
your remote so your team members can see it.

```sh
$ git push --set-upstream origin sameBranchName
```

This will make your branch visible on GitHub to other team members and set the upstream to push to
your specific branch. Double check to make sure your new branch is there by going to your
organization on GitHub, then to branches.

## Adding, Committing, and Pushing

##### If you've completed the steps above, you're ready to code on your branch now!

*You add and commit your files the same way you've always done it when you’re on a branch, but:*

> BEFORE YOU COMMIT, MAKE SURE YOU ARE ON YOUR BRANCH, NOT main.

After you add and commit your files, push your changes to your branch on GitHub:

```sh
$ git push origin sameBranchName
```

##### Now, if you’re ready to make a pull request in order to merge your branch's code with main, head over to GitHub:

* _Your Organization >> Branches >> Your Branch >> Compare & Pull Request_
* NEVER MERGE YOUR OWN PULL REQUEST UNTIL SOMEONE IN YOUR GROUP APPROVES IT!

## Merging main Into Your Branch

You should keep your branch up-to-date with main. First, commit any changes on your branch.
Make sure your work in good shape and committed, so it won't be a difficult process if there are conflicts.

```sh
# on your branch
$ git add -A
$ git commit -m “blah"
$ git checkout main
$ git pull origin main
```

Now, merge your branch with main. There could be conflicts if you haven't been pulling regularly.
No worries, this can usually be fixed in just a few minutes.

```sh
$ git checkout branchName
$ git merge main
```

#### If you tried a merge which resulted in complex conflicts and want to start over, you can recover:

```sh
# on your branch
$ git merge --abort
```

## Deleting Branches

When you are finished with a feature, and everything has been merged with the main branch via pull request,
you should delete your branch associated with that feature locally and on GitHub to keep things clean and organized.
You can delete it manually on GitHub by going to the organization then to branches, or you can delete it with:

```sh
$ git push origin :BranchName
```

The difference from before is simply the colon :

To delete your branch locally:

```sh
$ git branch -d branchName
```

To FORCE branch deletion locally:

```sh
$ git branch -D branchName
```

And to prune local references to deleted branches:

```sh
$ git remote prune origin
```

### _Important Reminders:_

* Tell your team every time a pull request has been merged with main. Don’t let your team members fall behind main.
* Pull often, just to be sure. Even if no one has told you about changes on main, pull anyways. It doesn’t hurt.
* Under Branches on GitHub you can find a visual representation of how far behind or head your branch is from main.
* Double check with team members before merging.
* Make sure you are on a branch before you start working. Get in the habit of checking.


Copied from 
https://gist.github.com/Alinaprotsyuk/3d58f8cd52eb03a11283d64beb0e083e#setting-up-your-branches
