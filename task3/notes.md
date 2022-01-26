# Task 3

Now that you have your custom kernel up and running, it's time to modify
it!

The tasks for this round is:
  - take the kernel git tree from Task 02 and modify the Makefile to
    and modify the EXTRAVERSION field.  Do this in a way that the
    running kernel (after modifying the Makefile, rebuilding, and
    rebooting) has the characters "-eudyptula" in the version string.
  - show proof of booting this kernel.  Extra cookies for you by
    providing creative examples, especially if done in intrepretive
    dance at your local pub.
  - Send a patch that shows the Makefile modified.  Do this in a manner
    that would be acceptable for merging in the kernel source tree.
    (Hint, read the file Documentation/SubmittingPatches and follow the
    steps there.)


## How to make a patch

1\. Setup `git send-email` by following [this link](https://stackoverflow.com/questions/68238912/how-to-configure-and-use-git-send-email-to-work-with-gmail-to-email-patches-to)

2\. Run `git log <file that's been modified>` to see some previous commit messages for style.

Usually the heading is : `<subsystem>/<sub-subsystem>: <descriptive comment>.`

Now commit and sign off:

`git commit <files> -s`

3\. Generate Patch file

`git format-patch HEAD~` or

`git format-patch HEAD~<number of commits to convert to patches>` to turn multiple commits into patch files.

They can reapplied with `git am <patchfile>`

4\. Lint your patch

`scripts/checkpatch.pl 0001-x86-build-don-t-add-maccumulate-outgoing-args-w-o-co.patch`

Also ensure to read the tree's own process / style, for example, [for the tip tree](https://www.kernel.org/doc/html/latest/process/maintainer-tip.html#changelog)

## How to submit a patch
5\. Email the patch to yourself to check

`git send-email 0001-x86-build-require-only-gcc-use-maccumulate-outgoing-.patch`

6\. get_maintainer.pl shows who to send your patch to, it can be incorporated into git send-email as shown below.

	./scripts/get_maintainer.pl 0001-x86-build-don-t-add-maccumulate-outgoing-args-w-o-co.patch
	Person A <person@a.com> (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT))
	Person B <person@b.com> (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT))
	Person C <person@c.com> (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT))
	x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT))
	linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND 64-BIT))

Also do a git blame on the file to check who has worked on it a lot and add them.
 
Ensure to put the maintainers in the "To" field, rather than "Cc", to ensure they actually see it

Use this script to send the patch in.

	$ git send-email \
	--to-cmd='./scripts/get_maintainer.pl --norolestats 0001-my.patch' \
	--cc person@a.com \
	0001-my.patch

I have not used this yet but it looks like this process can be further streamlined:

	[sendemail.linux]
		tocmd ="`pwd`/scripts/get_maintainer.pl --nogit --nogit-fallback --norolestats --nol"
		cccmd ="`pwd`/scripts/get_maintainer.pl --nogit --nogit-fallback --norolestats --nom"

To submit a patch, I just type:

`git send-email --identity=linux ./0001-my-fancy-patch.patch`

and let --to and --cc to be populated automatically.


7.\ Responding to feedback:

`git commit <changed files> --amend`

`git format-patch -v2 HEAD~`

In gmail, when viewing the message I want to respond to, you can click “Show Original” from the dropdown near the reply button. From there, copy the MessageID from the top (everything in the angle brackets, but not the brackets themselves). Finally, we send the patch:

	$ git send-email \
	--cc-cmd='./scripts/get_maintainer.pl --norolestats 0001-my.patch' \
	--cc person@a.com \
	--in-reply-to 2017datesandletters@somehostname \
	0001-my.patch

## Extra details	

I’ve added this handy shell function to my ~/.zshrc:

function kpatch () {
  patch=$1
  shift
  git send-email \
    --cc-cmd="./scripts/get_maintainer.pl --norolestats $patch" \
    $@ $patch
}

To invoke:

`kpatch 0001-Input-mousedev-fix-implicit-conversion-warning.patch --cc anyone@else.com`

